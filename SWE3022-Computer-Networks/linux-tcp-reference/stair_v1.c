#include <linux/module.h>
#include <linux/kernel.h>
#include <net/tcp.h>

struct minsu {
    /* inet_csk_ca(sk) -> inet_connection_sock's private storage
        maximum: 13 * 8 bytes
    */
    
    u32 prior_rtt;      /* prior rtt */
    s32 rtt_vector;     /* rtt vector */

    u32 max_cwnd;       /* loss occured cwnd */

    u32 stage_cnt;            /* ack count */
    u32 stage_thresh;   /* threshold of stair stage */

};

void minsu_debug(struct tcp_sock *tp, struct minsu *ca, const char *str)
{
    printk(KERN_INFO "[%d] - %s -\n\
        \ttp->snd_cwnd: %d\ttp->snd_cwnd_cnt: %d\ttp->snd_ssthresh: %d\n\
        \tca->max_snd: %d \tca->stage_thresh: %d\tca->stage_cnt: %d\n",
        get_current()->pid, str,
        tp->snd_cwnd, tp->snd_cwnd_cnt, tp->snd_ssthresh,
        ca->max_cwnd, ca->stage_thresh, ca->stage_cnt
    );
}

static inline void minsu_reset(struct minsu *ca)
{
    ca->prior_rtt = 0;
    ca->rtt_vector = 0;

    ca->max_cwnd = 0;

    ca->stage_cnt = 0;
    ca->stage_thresh = 2;
}

static inline void minsu_stage_update(struct tcp_sock *tp, struct minsu *ca)
{
    ca->stage_cnt -= ca->stage_thresh;
    if(tp->snd_cwnd + 1 > ca->max_cwnd ||
        (ca->max_cwnd - tp->snd_ssthresh) / ca->stage_thresh <= 1) {
        printk(KERN_INFO "Stage update phase: Reach to max\n");
        tp->snd_cwnd = ca->max_cwnd;
        tp->snd_ssthresh *= 2;
        ca->max_cwnd *= 2;

        ca->stage_thresh = 2;
    } else {
        printk(KERN_INFO "Stage update phase: Normal\n");
        ca->stage_thresh *= 2;
    }
}

// struct ack_sample {
//     u32 pkts_acked;
//     s32 rtt_us;
//     u32 in_flight;
// };

void minsu_acked(struct sock *sk, const struct ack_sample *sample)
{
    // struct tcp_sock *tp = tcp_sk(sk);
    struct minsu *ca = inet_csk_ca(sk);
    
    if(sample->rtt_us < 0)
        return;
    
    ca->stage_cnt++;
}

// enum tcp_ca_event {
// 	CA_EVENT_TX_START,	/* first transmit when no packets in flight */
// 	CA_EVENT_CWND_RESTART,	/* congestion window restart */
// 	CA_EVENT_COMPLETE_CWR,	/* end of congestion recovery */
// 	CA_EVENT_LOSS,		/* loss timeout */
// 	CA_EVENT_ECN_NO_CE,	/* ECT set, but not CE marked */
// 	CA_EVENT_ECN_IS_CE,	/* received CE marked IP packet */
// };

void minsu_cwnd_event(struct sock *sk, enum tcp_ca_event ev)
{
    
}

void minsu_state(struct sock *sk, u8 new_state)
{
    struct minsu *ca = inet_csk_ca(sk);

    minsu_debug(tcp_sk(sk), inet_csk_ca(sk), "before loss");
    switch(new_state) {
    case TCP_CA_Loss:
        printk(KERN_INFO "[EVENT] LOSS occured\n");
        minsu_reset(ca);
        break;
    }
    minsu_debug(tcp_sk(sk), inet_csk_ca(sk), "after loss");
}

void tcp_reno_init(struct sock *sk)
{
    struct minsu *ca = inet_csk_ca(sk);
    minsu_reset(ca);

    /* Initialize congestion control specific variables here */
    tcp_sk(sk)->snd_ssthresh = TCP_INFINITE_SSTHRESH; // Typically, this is a high value
    tcp_sk(sk)->snd_cwnd = 1; // Start with a congestion window of 1
}

u32 tcp_reno_ssthresh(struct sock *sk)
{
    /* Halve the congestion window, min 2 */
    const struct tcp_sock *tp = tcp_sk(sk);
    
    struct minsu *ca = inet_csk_ca(sk);
    if(ca->max_cwnd < tp->snd_cwnd)
        ca->max_cwnd = tp->snd_cwnd;
    
    return max(tp->snd_cwnd >> 1U, 2U);
}

void tcp_reno_cong_avoid(struct sock *sk, u32 ack, u32 acked)
{
    struct tcp_sock *tp = tcp_sk(sk);
    struct minsu *ca = inet_csk_ca(sk);
    // printk(KERN_INFO "[%d] tp->snd_cwnd is %d\n", get_current()->pid, tp->snd_cwnd);

    if (!tcp_is_cwnd_limited(sk))
        return;

    if (tp->snd_cwnd <= tp->snd_ssthresh) {
        /* In "slow start", cwnd is increased by the number of ACKed packets */
        minsu_debug(tp, ca, "before ss");
        acked = tcp_slow_start(tp, acked);
        minsu_debug(tp, ca, "after ss");
        if (!acked)
            return;
    }
    /* In "congestion avoidance", cwnd is increased by 1 full packet
        * per round-trip time (RTT), which is approximated here by the number of
        * ACKed packets divided by the current congestion window. */
    
    /* -- minsu --
        Stair version
    */
    if(ca->stage_cnt >= ca->stage_thresh) {
        u32 amount = (ca->max_cwnd - tp->snd_ssthresh) / ca->stage_thresh;
        
        minsu_debug(tp, ca, "before ai");
        tcp_cong_avoid_ai(tp, 1, amount);
        minsu_debug(tp, ca, "after ai");

        minsu_debug(tp, ca, "before update");
        minsu_stage_update(tp, ca);
        minsu_debug(tp, ca, "after update");
    }

    /* Ensure that cwnd does not exceed the maximum allowed value */
    tp->snd_cwnd = min(tp->snd_cwnd, tp->snd_cwnd_clamp);
}

u32 tcp_reno_undo_cwnd(struct sock *sk)
{
    /* Undo the cwnd changes during congestion avoidance if needed */

    /* -- minsu --
        Change to Reno version
    */
    const struct tcp_sock *tp = tcp_sk(sk);
    return max(tp->snd_cwnd, tp->prior_cwnd);
}

/* This structure contains the hooks to our congestion control algorithm */
static struct tcp_congestion_ops tcp_reno_custom = {
    .init           = tcp_reno_init,
    .ssthresh       = tcp_reno_ssthresh,
    .cong_avoid     = tcp_reno_cong_avoid,
    .undo_cwnd      = tcp_reno_undo_cwnd,

    .set_state      = minsu_state,
    .cwnd_event     = minsu_cwnd_event,
    .pkts_acked     = minsu_acked,

    .owner          = THIS_MODULE,
    .name           = "reno_custom",
};

/* Initialization function of this module */
static int __init tcp_reno_module_init(void)
{
    /* Register the new congestion control */
    BUILD_BUG_ON(sizeof(struct tcp_congestion_ops) != sizeof(struct tcp_congestion_ops));
    if (tcp_register_congestion_control(&tcp_reno_custom))
        return -ENOBUFS;
    return 0;
}

/* Cleanup function of this module */
static void __exit tcp_reno_module_exit(void)
{
    /* Unregister the congestion control */
    tcp_unregister_congestion_control(&tcp_reno_custom);
}

module_init(tcp_reno_module_init);
module_exit(tcp_reno_module_exit);

MODULE_AUTHOR("nethw");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TCP Reno Congestion Control");         