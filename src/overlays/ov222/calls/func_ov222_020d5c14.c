/* Notify func_ov222_020d2dec with the child fields, then dispatch. */
extern void func_ov222_020d2dec(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov222_020d5c44(void);
void func_ov222_020d5c14(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov222_020d2dec(*(int *)child, *(int *)(child + 0x78));
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov222_020d5c44);
}
