/* Equivalent, readable C. NOT byte-exact: size and structure match exactly, but
 * mwcc colors the loaded word `v` into r1 where the original keeps it in r2 (and
 * keeps the resource pointer live in r0 across both loads). A 1-register coloring
 * tie — unsteerable across load ordering and temp placement. The asm stub keeps
 * the blob byte-exact.
 *
 * Zero a 0xc-byte handle then bind it to the resource `param_2` loaded via
 * func_0201ef9c: store the resource pointer, copy its second word, and cache
 * ptr + its first word as an end marker. */
extern void MI_CpuFill8(void *dst, int val, int n);
extern int *func_0201ef9c(char *src, int kind);

void func_ov010_0204cac0(unsigned int *param_1, char *param_2) {
    int *p;
    int v;
    MI_CpuFill8(param_1, 0, 0xc);
    p = func_0201ef9c(param_2, 0xe);
    *param_1 = (unsigned int)p;
    v = *p;
    param_1[1] = p[1];
    param_1[2] = *param_1 + v;
}
