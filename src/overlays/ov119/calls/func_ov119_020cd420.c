/* Set animation state 1 then dispatch via func_0203c634 with handler
 * func_ov119_020cd454. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov119_020cd454(void);
void func_ov119_020cd420(int param_1) {
    func_ov107_020c9264(*(int *)(*(int *)(param_1 + 4)), 1, 1);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov119_020cd454);
}
