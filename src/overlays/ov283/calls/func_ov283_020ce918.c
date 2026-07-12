/* Only when bit 0 of *(obj)+0x17a is set, play the anim (ov107 mode 4) and register the handler. */
struct bit0 { unsigned char b : 1; };
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov283_020ce97c(int);
void func_ov283_020ce918(int param_1) {
    int obj = *(int *)*(int *)(param_1 + 4);
    if (((struct bit0 *)(obj + 0x17a))->b == 0) return;
    func_ov107_020c9264(obj, 4, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov283_020ce97c);
}
