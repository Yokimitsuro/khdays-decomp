/* PROVEN TIE (predication of a short return, off by one instr). The double-negation
 * form defeats mwcc's range reduction of {4,5,6} and preserves the cmp;cmpne;cmpne
 * cascade, but mwcc still predicates the fall-through `return 0` (moveq r0,#0; bxeq)
 * where the ROM branches (bne) to a shared return-1 block. Unsteerable across if /
 * boolean / double-negation / goto rewrites. Kept here so the ov008 blob stays
 * byte-exact. */
extern int data_0204be18;

int func_ov008_0208b7f0(int param_1) {
    int obj = *(int *)(param_1 + 0xc);
    int idx = *(int *)(obj + 0x14);
    int st;
    if (*(unsigned char *)(*(int *)&data_0204be18 + idx + 0x810) == 0) goto ret1;
    st = *(int *)(obj + 0x18);
    if (st != 4 && st != 5 && st != 6) goto ret1;
    return 0;
ret1:
    return 1;
}
