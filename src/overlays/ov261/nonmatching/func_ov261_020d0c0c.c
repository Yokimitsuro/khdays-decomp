/*
 * func_ov261_020d0c0c  (204 bytes) — node state-entry callback.
 *
 * Was previously committed in calls/ but does NOT verify byte-exact (violated the
 * "no non-matching .c in calls/" rule); moved here. This version is IMPROVED over
 * the old calls/ one — swapping the b1c/b28 stack-buffer declaration order fixed
 * the buffer-slot mismatch (b28@sp+0, b1c@sp+0xc). The SOLE remaining diff is a
 * register-coloring tie on the /15 division result: the orig builds it in the
 * callee-saved r6 (`smull r1,r6,..; add r6,..; add r6,..; str r6,[state,#0x3c]`)
 * then reuses r6 for the next block's `sub`; mwcc colors the dead-after-store
 * result into the scratch ip instead. The value dies at its store, so no source
 * form (block-scoped temp, inline expr) makes mwcc prefer a callee-saved reg.
 * Unsteerable coloring class. asm stub stays byte-exact.
 */
extern void func_ov261_020d0348();
extern void func_0202f384();
extern void VEC_Subtract();
extern void func_01ff8d18();
extern int func_01ff8bf8();
extern void func_ov107_020c5af8();
extern void func_0203c634(void *obj, int idx, void *value);
extern int data_02042258[];
extern void func_ov261_020d0cd8(void);
void func_ov261_020d0c0c(int *node) {
    int *state = (int *)node[1];
    state[0xf] = *(int *)(*node + 0x2c) * 0x1e / 15;
    {
        int sub = *(int *)(*state + 0x3a8);
        unsigned int b1c[3], b28[3];
        func_ov261_020d0348(state + 7, sub + 0x74, state[1]);
        func_0202f384(b1c, state + 3, data_02042258);
        VEC_Subtract(sub + 0x74, state[1], b28);
        func_01ff8d18(b28, b28);
        if ((int)func_01ff8bf8(b1c, b28) > 0xf00) {
            state[0x10] = 0;
            func_ov107_020c5af8(*state, 0x179, 4, state[1]);
            func_0203c634(node, *(signed char *)(node + 8), func_ov261_020d0cd8);
        }
    }
}
