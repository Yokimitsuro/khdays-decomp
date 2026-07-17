/*
 * func_ov194_020cdd54 -- UNFINISHED. 264 vs 256: the hw60 hi-byte `|= 0x40` reassemble is 2
 * instructions (8 bytes) over. x3 family. Everything ELSE is byte-exact.
 *
 * WHAT IT DOES: age the timer (state[0x15]); state[5] = (owner delta) * 30 / 10 (division at the
 * HEAD, magic 0x66666667 asr#2 = /10, base *self -- matches, per the head-vs-tail rule). Re-acquire
 * the target; if present, aim from target+0x74 to state[0x10] and store the heading (atan2) in
 * state[4]. Then, once the sub-node at state[1]+0xad is idle: fire events 5 and (via *state+0x3d0)
 * 020c9ee8, SET bit 6 of the hw60 hi byte at *state+0x60, clear state[0xc], and advance.
 *
 * THE GAP is the documented hw60 STANDALONE `->hi |= K` tie. The ROM reassembles with:
 *      ldrh ip ; lsl r3,ip,#0x10 ; lsr r3,r3,#0x18 ; orr r3,r3,#0x40 ; bic ip,ip,#0xff00 ;
 *      lsl r3,r3,#0x18 ; orr r3,ip,r3,lsr #16 ; strh r3
 * i.e. extract hi, OR the bit, `bic` the old hi out, recombine. Neither the bitfield form
 * (`struct hw60{u16 lo:8,hi:8;}; ->hi |= 0x40`) nor the explicit extract/reassemble reproduces
 * that compaction -- both add a redundant mask (264, +8B). This is exactly the deferred-ties
 * "hw60 ->hi |= K adds a redundant lsl/lsr mask, +8B" entry, and it is STANDALONE here (no prior
 * hi-byte write to establish the 0..0xff range), which codegen-cracks.md notes is the case that
 * ties. The bitfield form matches only as the 2nd+ op in a chain.
 *
 * So the function is one catalogued tie from done; the division-at-head, the aim, and the atan2
 * are all byte-exact. If the standalone hw60 |= is ever cracked, this drops straight in.
 */
extern int func_ov107_020cab14(int obj, int out);
extern void func_0203c634(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern int func_ov194_020cde54;

void func_ov194_020cdd54(int *self) {
    int *state = (int *)self[1];
    int aim[3];
    int target;

    state[0x15] += *(int *)(*self + 0x2c);
    state[5] = *(int *)(*self + 0x2c) * 0x1e / 10;
    target = func_ov107_020cab14(*state, 0);
    state[2] = target;
    if (target != 0) {
        VEC_Subtract((void *)(target + 0x74), (void *)state[0x10], aim);
        state[4] = func_020050b4(aim[0], aim[2]);
    }
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        unsigned short u;
        func_ov107_020c9264(*state, 5, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x3d0), 1, 0);
        u = *(unsigned short *)(*state + 0x60);
        *(unsigned short *)(*state + 0x60) =
            (unsigned short)(u & 0xff |
                (unsigned short)(((((unsigned)u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
        state[0xc] = 0;
        func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov194_020cde54);
    }
}
