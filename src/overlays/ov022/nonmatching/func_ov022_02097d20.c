/* NONMATCHING: scheduling/addressing tie. Original re-reads field@+0x4b4 after
 * the call (no caching: push {r4,lr}) and uses [r4,#0x4b4] for BOTH stores; mwcc
 * either caches the field across the call (extra callee-saved regs) or splits the
 * predicated clamp store's address (add r,base,#0xb4; strmi [r,#0x400]). Same
 * logic: subtract func_ov022_02083f90() from field@+0x4b4, clamp to >= 0. */
extern int func_ov022_02083f90(void);
void func_ov022_02097d20(int arg0) {
    if (*(int *)(arg0 + 0x4b4) != 0) {
        int v = *(int *)(arg0 + 0x4b4) - func_ov022_02083f90();
        *(int *)(arg0 + 0x4b4) = v;
        if (v < 0) *(int *)(arg0 + 0x4b4) = 0;
    }
}
