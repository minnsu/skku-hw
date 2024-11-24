#include <linux/module.h>
#include <linux/kernel.h>
#include <net/tcp.h>

// ------------------------ Minsu Added ------------------------

/* minsu TCP variables */
struct minsu {
    /* inet_csk_ca(sk) -> private storage for custom algorithm */
    /* maximum 13 * 8 bytes */
    
    u32 limit_cnt;          /* ack count limit */
    u32 cnt;                /* ack count */

    u32 last_max_cwnd;      /* last maximum snd_cwnd */
};

static inline void minsu_init(struct minsu *ca)
{
    ca->limit_cnt = 2;
    ca->cnt = 0;
    ca->last_max_cwnd = 0;
}
static inline void minsu_reset(struct minsu *ca)
{
    ca->limit_cnt *= 2;
    ca->cnt = 0;
}

void minsu_state(struct sock *sk, u8 new_state)
{ /* call before changing ca_state */
    
    // printk(KERN_INFO "[%d] [CHANGE CA STATE]", get_current()->pid);
    if(new_state == TCP_CA_Loss)
        minsu_reset(inet_csk_ca(sk));
}

// struct ack_sample {
//     u32 pkts_acked;
//     s32 rtt_us;
//     u32 in_flight;
// };
void minsu_pkts_acked(struct sock *sk, const struct ack_sample *sample)
{ /* call when ack arrived */
    struct tcp_sock *tp = tcp_sk(sk);
    struct minsu *ca = inet_csk_ca(sk);

    printk(KERN_INFO "[%d] [ACKED] acked: %d rtt: %dus not ACKed(in-flights): %d at %llu\n", get_current()->pid, sample->pkts_acked, sample->rtt_us, sample->in_flight, ktime_get());

    if(sample->rtt_us < 0)
        return;

    ca->cnt++;
}

// enum tcp_ca_event {
// 	CA_EVENT_TX_START,	 /* first transmit when no packets in flight */
// 	CA_EVENT_CWND_RESTART,	/* congestion window restart */
// 	CA_EVENT_COMPLETE_CWR,	/* end of congestion recovery */
// 	CA_EVENT_LOSS,		/* loss timeout */
// 	CA_EVENT_ECN_NO_CE,	/* ECT set, but not CE marked */
// 	CA_EVENT_ECN_IS_CE,	/* received CE marked IP packet */
// };

void minsu_cwnd_event(struct sock *sk, enum tcp_ca_event ev)
{ /* call when cwnd event occurs */
    struct minsu *ca = inet_csk_ca(sk);

    // printk(KERN_INFO "[%d] [CWND EVENT] ", get_current()->pid);
    switch(ev) {
        case CA_EVENT_TX_START:
            // printk("TX_START\n");
            break;
        case CA_EVENT_CWND_RESTART:
            // printk("CWND_RESTART\n");
            break;
        case CA_EVENT_COMPLETE_CWR:
            // printk("COMPLETE_CWR\n");
            break;
        case CA_EVENT_LOSS:
            // printk("LOSS\n");
            break;
        default:
            break;
    }
}

// --------------------------------------------------------------

void tcp_reno_init(struct sock *sk)
{
    /* Initialize congestion control specific variables here */

    struct minsu *ca = inet_csk_ca(sk);
    minsu_init(ca);

    tcp_sk(sk)->snd_ssthresh = TCP_INFINITE_SSTHRESH; // Typically, this is a high value
    tcp_sk(sk)->snd_cwnd = 1; // Start with a congestion window of 1
}

u32 tcp_reno_ssthresh(struct sock *sk)
{
    /* Halve the congestion window, min 2 */
    const struct tcp_sock *tp = tcp_sk(sk);
    
    struct minsu *ca = inet_csk_ca(sk);
    if(ca->last_max_cwnd < tp->snd_cwnd)
        ca->last_max_cwnd = tp->snd_cwnd;

    return max(tp->snd_cwnd >> 1U, 2U);
}

void tcp_reno_cong_avoid(struct sock *sk, u32 ack, u32 acked)
{
    struct tcp_sock *tp = tcp_sk(sk);
    struct minsu *ca = inet_csk_ca(sk);

    printk(KERN_INFO "[%d] snd_cwnd: %d / ssthresh: %d / max_cwnd: %d\n", get_current()->pid, tp->snd_cwnd, tp->snd_ssthresh, ca->last_max_cwnd);

    if (!tcp_is_cwnd_limited(sk))
        return;

    if (tp->snd_cwnd <= tp->snd_ssthresh) {
        /* In "slow start", cwnd is increased by the number of ACKed packets */
        acked = tcp_slow_start(tp, acked);
        if (!acked)
            return;
    }
    /* In "congestion avoidance", cwnd is increased by 1 full packet
        * per round-trip time (RTT), which is approximated here by the number of
        * ACKed packets divided by the current congestion window. */
    
    /* -- minsu defined -- */
    if(ca->cnt >= ca->limit_cnt) {
        // tcp_cong_avoid_ai(tp, tp->snd_cwnd, acked);
        tp->snd_cwnd = (tp->snd_cwnd + ca->last_max_cwnd) / 2;
        minsu_reset(ca);
        if(tp->snd_cwnd + 1 >= ca->last_max_cwnd)
            tp->snd_ssthresh *= 2;
    }

    /* Ensure that cwnd does not exceed the maximum allowed value */
    tp->snd_cwnd = min(tp->snd_cwnd, tp->snd_cwnd_clamp);
}

u32 tcp_reno_undo_cwnd(struct sock *sk)
{
    /* Undo the cwnd changes during congestion avoidance if needed */
    
    /* -- minsu defined --
        change to original reno,
        because tcp_cubic use same undo_cwnd function
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

    /* -- minsu defined -- */
    .set_state      = minsu_state,
    .pkts_acked     = minsu_pkts_acked,
    .cwnd_event     = minsu_cwnd_event,
    /* ------------------- */

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
