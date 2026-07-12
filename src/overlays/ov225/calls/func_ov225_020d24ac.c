/* Notify func_ov225_020d0f1c with the child fields, clear its flags at +0x75/+0x76, then
 * dispatch via func_0203c634 (handler func_ov225_020d24e8). */
extern void func_ov225_020d0f1c(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov225_020d24e8(void);
void func_ov225_020d24ac(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov225_020d0f1c(*(int *)child, *(int *)(child + 0x78));
    *(unsigned char *)(child + 0x75) = 0;
    *(unsigned char *)(child + 0x76) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov225_020d24e8);
}
