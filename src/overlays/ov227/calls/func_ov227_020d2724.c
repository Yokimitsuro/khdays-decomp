/* Notify func_ov227_020d1158 with the child fields, clear its flags at +0x75/+0x76, then
 * dispatch via func_0203c634 (handler func_ov227_020d2760). */
extern void func_ov227_020d1158(int a, int b);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov227_020d2760(void);
void func_ov227_020d2724(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov227_020d1158(*(int *)child, *(int *)(child + 0x78));
    *(unsigned char *)(child + 0x75) = 0;
    *(unsigned char *)(child + 0x76) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov227_020d2760);
}
