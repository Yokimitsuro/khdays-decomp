/* Notify func_ov224_020d0fe4 with the child fields, then dispatch. */
extern void func_ov224_020d0fe4(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov224_020d3e4c(void);
void func_ov224_020d3e1c(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov224_020d0fe4(*(int *)child, *(int *)(child + 0x78));
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov224_020d3e4c);
}
