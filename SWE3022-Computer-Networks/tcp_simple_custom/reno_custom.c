#include <linux/module.h>
#include <linux/kernel.h>
#include <net/tcp.h>

u32 tcp_id = 0;
struct minsu {
    u32 id;                 /* DEBUG VAR: tcp identifier */
    u32 numerator;          /* factor: numerator */
    u32 denominator;        /* factor: denominator */
    u32 goal_cwnd;          /* goal cwnd of stage */
    u32 last_max_cwnd;      /* last loss's cwnd */
    
    enum _phase {
        zero,
        one,
        two,
        three,
        four,
        clear
    } phase;                /* stage phase */
};

void debug_message(const struct tcp_sock *tp, const struct minsu *ca, const char *str)
{
    printk(KERN_INFO "[%d] * %s *\n\tcwnd: %-6d\tcwnd_cnt: %-6d\tssthresh: %-6d\n\tgoal: %-6d\tmax_cwnd: %-6d\tfactor: %d / %d\n",
        ca->id, str,
        tp->snd_cwnd, tp->snd_cwnd_cnt, tp->snd_ssthresh,
        ca->goal_cwnd, ca->last_max_cwnd, ca->numerator, ca->denominator);
}

static inline void minsu_reset(struct minsu *ca, u8 new_id)
{
    if(new_id)
        ca->id = tcp_id++;
    
    ca->phase = zero;
    ca->numerator = 1;
    ca->denominator = 1;
    ca->goal_cwnd = 0;
    ca->last_max_cwnd = 0;
}

static inline void minsu_init(const struct tcp_sock *tp, struct minsu *ca)
{
    ca->phase = one;
    ca->numerator = 4;
    ca->denominator = 1;
    ca->goal_cwnd = tp->snd_ssthresh + (tp->snd_ssthresh >> 1);
    if( (ca->last_max_cwnd >> 1) != tp->snd_ssthresh) {
        ca->last_max_cwnd = 2 * tp->snd_ssthresh;
    }
}

static inline void minsu_update(struct tcp_sock *tp, struct minsu *ca)
{
    if( (ca->last_max_cwnd >> 1) != tp->snd_ssthresh) /* detect thresh force busting process */
        minsu_init(tp, ca);

    switch(ca->phase) {
    case one:
        ca->phase = two;
        
        ca->numerator = 2;
        ca->goal_cwnd += (tp->snd_ssthresh >> 2);
        break;
    case two:
        ca->phase = three;

        ca->numerator = 1;
        ca->denominator = 2;
        ca->goal_cwnd += (tp->snd_ssthresh >> 3);
        break;
    case three:
        ca->phase = four;

        ca->denominator = 4;
        ca->goal_cwnd = ca->last_max_cwnd;
        break;
    case four:
        ca->phase = clear;

        ca->denominator = 1;
        ca->goal_cwnd += tp->snd_ssthresh;
        break;
    case clear:
        minsu_reset(ca, 0);
        // tp->snd_ssthresh = tp->snd_cwnd;         /* transition to phase:zero */
        tp->snd_ssthresh = TCP_INFINITE_SSTHRESH; /* transition to slow start */
        break;
    default:
        printk(KERN_INFO "phase:zero can not enter this function!\n");
        break;
    }
}

static void minsu_state(struct sock *sk, u8 new_state)
{
    if(new_state == TCP_CA_Loss)
        minsu_reset(inet_csk_ca(sk), 0);
}


void tcp_reno_init(struct sock *sk)
{
    minsu_reset(inet_csk_ca(sk), 1);

    /* Initialize congestion control specific variables here */
    tcp_sk(sk)->snd_ssthresh = TCP_INFINITE_SSTHRESH; // Typically, this is a high value
    tcp_sk(sk)->snd_cwnd = 1; // Start with a congestion window of 1
}

u32 tcp_reno_ssthresh(struct sock *sk)
{
    /* Halve the congestion window, min 2 */
    const struct tcp_sock *tp = tcp_sk(sk);
    struct minsu *ca = inet_csk_ca(sk);

    /* last_max_cwnd is cwnd of last loss occured cwnd */
    ca->last_max_cwnd = tp->snd_cwnd;

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
        ca->phase = zero;
        /* In "slow start", cwnd is increased by the number of ACKed packets */
        acked = tcp_slow_start(tp, acked);
        if (!acked)
            return;
    }
    
    /* In "congestion avoidance", cwnd is increased by 1 full packet
        * per round-trip time (RTT), which is approximated here by the number of
        * ACKed packets divided by the current congestion window. */
    
    if(ca->phase == zero)
        minsu_init(tp, ca);

    // debug_message(tp, ca, "before avoidance");
    // printk("ACKED: %d\n", acked);

    tcp_cong_avoid_ai(tp, tp->snd_cwnd, acked * ca->numerator / ca->denominator);
    if(tp->snd_cwnd >= ca->goal_cwnd)
        minsu_update(tp, ca);
    
    // debug_message(tp, ca, "after avoidance");

    /* Ensure that cwnd does not exceed the maximum allowed value */
    tp->snd_cwnd = min(tp->snd_cwnd, tp->snd_cwnd_clamp);
}

u32 tcp_reno_undo_cwnd(struct sock *sk)
{
    /* Undo the cwnd changes during congestion avoidance if needed */
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