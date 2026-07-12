/* Accumulate the owner's rate (+0x2c) into the child timer (+0x3c); once it passes
 * 0x444, reset it and dispatch. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov138_020d1098(void);
void func_ov138_020d1054(int param_1) {
    int child = *(int *)(param_1 + 4);
    int c = *(int *)(child + 0x3c) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x3c) = c;
    if (c <= 0x444) return;
    *(int *)(child + 0x3c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov138_020d1098);
}
