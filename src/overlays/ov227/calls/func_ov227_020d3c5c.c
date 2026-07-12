/* Notify func_ov227_020d1158 with the child fields, then dispatch. */
extern void func_ov227_020d1158(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov227_020d3c8c(void);
void func_ov227_020d3c5c(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov227_020d1158(*(int *)child, *(int *)(child + 0x78));
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov227_020d3c8c);
}
