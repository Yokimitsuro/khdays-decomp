/* Rider watch tick (first rider): runs the +0x14 timer; once the +0x24 child's byte clears and
 * either of the actor's +0x3bc / +0x3be rider counters is empty, the cue at data_ov278_020d639c
 * entry 4 (byte 3 forced to 2) is sent through the +0x24 hook and the counters are floored at 1;
 * then the node dispatches null. */
struct Ov236RiderCounters { char pad[0xbc]; short cur; short max; };
extern void func_0203c634(void *obj, int idx, void *value);
extern unsigned short data_ov278_020d639c[];

void func_ov278_020d3194(int *node) {
    int *state = (int *)node[1];
    unsigned short pair[2];
    void (*cb)();

    state[5] += *(int *)(*node + 0x2c);
    if (*(unsigned char *)state[9] != 0) return;
    if (*(short *)(*state + 0x300 + 0xbc) == 0 || *(short *)(*state + 0x300 + 0xbe) == 0) {
        pair[1] = data_ov278_020d639c[9];
        pair[0] = data_ov278_020d639c[8];
        if (*(short *)(*state + 0x300 + 0xbc) < 1) ((struct Ov236RiderCounters *)(*state + 0x300))->cur = 1;
        if (*(short *)(*state + 0x300 + 0xbe) < 1) ((struct Ov236RiderCounters *)(*state + 0x300))->max = 1;
        ((unsigned char *)pair)[3] = 2;
        cb = *(void (**)())(*state + 0x24);
        if (cb != 0) cb(*state, pair, 4);
    }
    func_0203c634(node, *(signed char *)(node + 8), 0);
}
