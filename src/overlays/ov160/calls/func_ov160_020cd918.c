/* Attack wait tick of the ov160 enemy: the +0x3c timer accumulates the owner's rate. In phase
 * 0 (+0x54) past 0x22aa (both conditions in one test, which keeps the phase byte live) the data_ov160_020cf794[4..5] message pair is sent to the +0x24 hook
 * (arg 4), reaction 0x151 mode 6 fires at the +0x398 bone's +0x14 and phase 1 begins; in phase 1
 * past 0x23bb the [2..3] pair is sent and phase 2 begins. Once the +4 item is idle (+0xad) the
 * +0x44 delay is re-armed to a random value in [+0x224, +0x228], sub-state 2 is queued and the
 * state ends. */
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern int func_02023eb4(int bound);
extern void func_0203c634(int *node, int slot, void *cb);
extern unsigned short data_ov160_020cf794[];

void func_ov160_020cd918(int *node)
{
    int *state = (int *)node[1];
    unsigned short pairA[2];
    unsigned short pairB[2];
    unsigned short *pp;
    void (*cb)();
    int lo;
    int diff;

    state[0xf] += *(int *)(node[0] + 0x2c);
    if (*(unsigned char *)((char *)state + 0x54) == 0 && state[0xf] > 0x22aa) {
        pp = pairA;
        pp[1] = data_ov160_020cf794[5];
        pp[0] = data_ov160_020cf794[4];
        cb = *(void (**)())(*state + 0x24);
        if (cb != 0) cb(*state, pp, 4);
        func_ov107_020c5af8(*state, 0x151, 6, (void *)(*(int *)(*state + 0x398) + 0x14));
        *(unsigned char *)((char *)state + 0x54) = 1;
    } else if (*(unsigned char *)((char *)state + 0x54) == 1 && state[0xf] > 0x23bb) {
        pp = pairB;
        pp[1] = data_ov160_020cf794[3];
        pp[0] = data_ov160_020cf794[2];
        cb = *(void (**)())(*state + 0x24);
        if (cb != 0) cb(*state, pp, 4);
        *(unsigned char *)((char *)state + 0x54) = 2;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    lo = *(int *)(*state + 0x224);
    diff = *(int *)(*state + 0x228) - lo;
    if (diff < 0) {
        diff = -diff;
    }
    state[0x11] = lo + func_02023eb4(diff + 1);
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
