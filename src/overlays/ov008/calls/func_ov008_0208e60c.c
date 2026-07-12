/* Zero a 0xc-byte record, then set its +4/+8 handler slots from the source pair, falling back to
 * the default handlers 020342e8 / 020343cc when a slot is null. */
extern void MI_CpuFill8(void *dst, int val, int size);
extern void func_020342e8(void);
extern void func_020343cc(void);
void func_ov008_0208e60c(int param_1, int param_2) {
    int v;
    MI_CpuFill8((void *)param_1, 0, 0xc);
    v = *(int *)param_2;
    *(int *)(param_1 + 4) = v ? v : (int)&func_020342e8;
    v = *(int *)(param_2 + 4);
    *(int *)(param_1 + 8) = v ? v : (int)&func_020343cc;
}
