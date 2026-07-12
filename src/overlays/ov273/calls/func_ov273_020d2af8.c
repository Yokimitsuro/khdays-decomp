/* Reset +0xc/+0x14 and set +0x10 = -0x400; unless bit 0 of *(*(obj)+0x3dc)+0x394 is set,
 * clear bit 0 of *(obj)+0x434, play the anim (ov107 mode 0x18) and register the handler. */
struct sbit0 { int b : 1; };
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov273_020d2b60(int);
void func_ov273_020d2af8(int param_1) {
    int child = *(int *)(param_1 + 4);
    int obj;
    *(int *)(child + 0xc) = 0;
    *(int *)(child + 0x10) = -0x400;
    *(int *)(child + 0x14) = 0;
    obj = *(int *)child;
    if (((struct sbit0 *)(*(int *)(obj + 0x3dc) + 0x394))->b) return;
    *(int *)(obj + 0x434) &= ~1;
    func_ov107_020c9264(*(int *)child, 0x18, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov273_020d2b60);
}
