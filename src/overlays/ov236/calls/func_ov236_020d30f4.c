/* Recovery wait (first rider): runs the +0x14 timer; once the +0x24 child's byte clears pose
 * 0x10 plays and, for each empty rider counter (+0x3bc / +0x3be), the matching cue
 * (data_ov236_020d63e8 entries 3 / 1) goes through the +0x24 hook; the node moves to 020d31e0. */
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(void *obj, int idx, void *value);
extern unsigned short data_ov236_020d63e8[];
extern void func_ov236_020d31e0(void);

void func_ov236_020d30f4(int *node) {
    int *state = (int *)node[1];
    unsigned short pairA[2];
    unsigned short pairB[2];
    unsigned short *pp;
    void (*cb)();

    state[5] += *(int *)(*node + 0x2c);
    if (*(unsigned char *)state[9] != 0) return;
    func_ov107_020c9264(*state, 0x10, 0);
    if (*(short *)(*state + 0x300 + 0xbc) == 0) {
        pp = pairA;
        pp[1] = data_ov236_020d63e8[7];
        pp[0] = data_ov236_020d63e8[6];
        cb = *(void (**)())(*state + 0x24);
        if (cb != 0) cb(*state, pp, 4);
    }
    if (*(short *)(*state + 0x300 + 0xbe) == 0) {
        pp = pairB;
        pp[1] = data_ov236_020d63e8[3];
        pp[0] = data_ov236_020d63e8[2];
        cb = *(void (**)())(*state + 0x24);
        if (cb != 0) cb(*state, pp, 4);
    }
    func_0203c634(node, *(signed char *)(node + 8), func_ov236_020d31e0);
}
