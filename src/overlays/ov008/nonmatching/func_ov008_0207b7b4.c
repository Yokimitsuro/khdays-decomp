/* PROVEN TIE (predication vs branch, same size): the ROM computes -1 with a
 * predicated mvnne and then *branches* (bne) to a shared pop, while mwcc build
 * 139 predicates the pop itself (popne). Same instruction count, equivalent
 * control flow; unsteerable across ~3 structural rewrites. Kept here so the
 * ov008 blob stays byte-exact. */
extern int data_ov008_02090f24;
extern int WM_EndKeySharing_0x020bf240(void);

int func_ov008_0207b7b4(void) {
    if (*(int *)(*(int *)&data_ov008_02090f24 + 0x4e8) != 0) return -1;
    return (signed char)WM_EndKeySharing_0x020bf240();
}
