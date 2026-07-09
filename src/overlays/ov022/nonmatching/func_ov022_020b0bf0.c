/* NONMATCHING: constant-materialization tie. The original holds 0 in a register
 * early (also the return default) and derives both sentinels from it:
 *   mov r0,#0 ; sub r2,r0,#0x1000 (=-0x1000) ; subeq ip,r0,#0x80000001 (=0x7fffffff)
 * mwcc instead materializes -0x1000 via mov+rsb and 0x7fffffff via mvn, and does
 * not reuse a held zero, so the body is longer. Structure/logic are identical.
 * Semantics: bounds-check arg1 against [lo=base+0x10, hi=base+0x14] where a hi of
 * -0x1000 means "unbounded" (INT_MAX); base = *(*(arg0+0x470)+0x14). */
int func_ov022_020b0bf0(int arg0, int arg1) {
    int base = *(int *)(*(int *)(arg0 + 0x470) + 0x14);
    int hi = *(int *)(base + 0x14);
    if (hi == -0x1000) hi = 0x7fffffff;
    if (arg1 < *(int *)(base + 0x10)) return 0;
    return arg1 < hi;
}
