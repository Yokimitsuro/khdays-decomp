/* NONMATCHING: loop-invariant address-hoisting tie, ~8 bytes long. The original
 * holds only obj (r8) and the counter (r7) and RECOMPUTES the fixed sub-addresses
 * (obj+0x28, obj+0x108, obj+0x48) inline each iteration; mwcc hoists all of them
 * into callee-saved registers before the loop, forcing four extra pushes
 * (sb/sl/fp/r3). No source form found to suppress the loop-invariant hoist.
 * Semantics: for slots 0..4, if obj+0x130 is null bind track i to obj+0x108,
 * else free the old handle at obj+i*4+0x34 (via 02014dc4), clear it, and bind
 * track i to *(obj+0x130); then zero track i. */
extern void func_02014dc4(unsigned int *a, int b);
extern void func_0202accc(int a, int b, int c, int d);
extern void func_01fff774(int a, int b, int c);

void func_ov022_020914a0(int obj, short arg1) {
    unsigned int i = 0;
    do {
        if (*(int *)(obj + 0x130) == 0) {
            func_0202accc(obj + 0x28, i & 0xffff, obj + 0x108, arg1);
        } else {
            int slot = *(int *)(obj + i * 4 + 0x34);
            if (slot != 0) {
                func_02014dc4((unsigned int *)(obj + 0x48), slot);
                *(int *)(obj + i * 4 + 0x34) = 0;
            }
            func_0202accc(obj + 0x28, i & 0xffff, *(int *)(obj + 0x130), arg1);
        }
        func_01fff774(obj + 0x28, i & 0xffff, 0);
        i = i + 1;
    } while ((int)i < 5);
}
