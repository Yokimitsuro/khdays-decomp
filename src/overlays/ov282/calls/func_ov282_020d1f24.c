/*
 * func_ov282_020d1f24 -- pick the reaction: charge if the target is far enough, otherwise idle.
 * Does nothing while the byte at *state[3] is set. func_ov107_020cab14 hands back the target and
 * the SQUARED separation, so the gap is its square root less the target's radius (+0x80) and the
 * owner's (+0x80). A gap of 0xa000 or more parks the owner in state 5 and dispatches; anything
 * closer rolls a fresh delay into state[0x1b] from the owner's [+0x224, +0x228] range and parks
 * it in state 2.
 *
 * Parked at a symmetric r6/r7 swap between `target` and `owner`, with the note recording (rightly)
 * that caching `*state` in an `owner` local is load-bearing -- it keeps both values in callee-saved
 * registers across FX_Sqrt and is what fixed an earlier 16-byte gap. Two more steps close it:
 *  - the ROM stores the acquire result straight out of r0 and keeps the flag-setting copy in r7,
 *    so the STORE must come first and the local be bound from the slot
 *    (`state[4] = acquire(...); target = state[4];`), not the other way round;
 *  - `owner` must then be a FUNCTION-SCOPE declaration, because the swap is decided by declaration
 *    order and a block-scoped local is not in that ordering at all. tools/declperm.py picks the
 *    order out; every matching one has `target` last.
 */

extern int  func_ov107_020cab14(int obj, void *out);
extern int  FX_Sqrt(int x);
extern int  func_02023eb4(int mul);
extern void func_0203c634(int self, int idx, int cb);

void func_ov282_020d1f24(int *self) {
    int *state;
    int out;
    int *owner;
    int target;
    state = (int *)self[1];

    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    state[4] = func_ov107_020cab14(*state, &out);
    target = state[4];
    if (target != 0) {
        owner = (int *)*state;
        out = FX_Sqrt(out) - *(int *)(target + 0x80) - owner[0x20];
        if (out >= 0xa000) {
            *(char *)(*state + 0x1c7) = 5;
            func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
            return;
        }
    }
    {
        int lo = *(int *)(*state + 0x224);
        int d = *(int *)(*state + 0x228) - lo;
        state[0x1b] = lo + func_02023eb4((d < 0 ? -d : d) + 1);
    }
    *(char *)(*state + 0x1c7) = 2;
    func_0203c634((int)self, *(signed char *)((int)self + 0x20), 0);
}
