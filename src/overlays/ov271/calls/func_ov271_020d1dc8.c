/* Enter the attack state: refresh the owner, convert the owner's per-frame delta into the
 * per-second budget at state[0x18], fire attack 6 with flag 1, raise bit 3 of the owner halfword
 * at +0x1ae, and send the canned 4-byte block from the config table to the notify hook before
 * clearing the timer and handing off.
 *
 * Matched byte-exact 2026-07-23, closing an old park. Two things were wrong in it. The divisor is
 * 15, not 30: the magic is the same 0x88888889 either way and only the final shift tells them
 * apart (asr #3 = /15, asr #4 = /30). And the config pair has to be a STRUCT-TYPED GLOBAL copied
 * with a plain struct assignment, with `state` loaded BEFORE it: the struct copy is one unit for
 * the scheduler, so the state load drops into the gap between the two halfword loads and the two
 * halfword stores, which is exactly where the ROM has it. Reading the pair as two array elements
 * lets the scheduler split it and the load lands one slot early or two slots late.
 *
 * One of three byte-identical siblings. */
struct pt { unsigned short a, b; };
extern void func_ov271_020d0710(int self);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(int self, int idx, int cb);
struct blk { unsigned short pad[6]; struct pt p; };
extern struct blk data_ov271_020d36a0;
extern void func_ov271_020d1e7c(void);

void func_ov271_020d1dc8(int *self) {
    struct pt pt;
    void (*fp)(int, void *, int);
    int *state;

    state = (int *)self[1];
    pt = data_ov271_020d36a0.p;
    func_ov271_020d0710((int)self);
    state[0x18] = *(int *)(*self + 0x2c) * 0x1e / 15;
    func_ov107_020c9264(*state, 6, 1);
    *(unsigned short *)(*state + 0x1ae) |= 8;
    fp = *(void (**)(int, void *, int))(*state + 0x24);
    if (fp != 0) {
        fp(*state, &pt, 4);
    }
    state[0x14] = 0;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), (int)&func_ov271_020d1e7c);
}
