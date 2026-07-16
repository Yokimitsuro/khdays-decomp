/* NONMATCHING: semantics correct; ties on register allocation of the loaded flags halfword
 * (ROM keeps it in r0 / the param reg, mwcc uses r1), a pure r0<->r1 swap cascading through
 * the two bit-test shifts. Not steerable via local vs inline. */
/* func_ov008_02058bac -- ov008 per-frame check for a pending "back/cancel" on a menu object.
 * flags = *(u16*)(obj+0x5c6): if bit 7 is set (still busy) do nothing; if bit 5 is set, close the
 * sub-panel (func_ov008_02057c78(0)) and fire UI event 3 (func_02033b78(0,3)). Otherwise, only if
 * cue 0x200c is active (func_02023588) and a live entry exists (func_ov008_0204ed20), mark that
 * entry (|4 at +2) and enter mode 8 (func_ov008_0205714c). */
extern void func_ov008_02057c78(int a);
extern void func_02033b78(int a, int b);
extern int  func_02023588(int cue);
extern int  func_ov008_0204ed20(void);
extern void func_ov008_0205714c(int mode);

void func_ov008_02058bac(int param_1) {
    if (((unsigned int)*(unsigned short *)(param_1 + 0x5c6) << 0x18) >> 0x1f) {
        return;
    }
    if (((unsigned int)*(unsigned short *)(param_1 + 0x5c6) << 0x1a) >> 0x1f) {
        func_ov008_02057c78(0);
        func_02033b78(0, 3);
        return;
    }
    if (func_02023588(0x200c) == 0) {
        return;
    }
    {
        int entry = func_ov008_0204ed20();
        if (entry == 0) {
            return;
        }
        *(unsigned char *)(entry + 2) |= 4;
        func_ov008_0205714c(8);
    }
}
