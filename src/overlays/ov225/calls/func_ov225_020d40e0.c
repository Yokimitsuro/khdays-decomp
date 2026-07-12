/* Notify func_ov225_020d0f1c with the child fields, then dispatch. */
extern void func_ov225_020d0f1c(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov225_020d4110(void);
void func_ov225_020d40e0(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov225_020d0f1c(*(int *)child, *(int *)(child + 0x78));
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov225_020d4110);
}
