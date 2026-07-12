/* Play the anim (ov107 mode 0xd,1), clear bit 0x40 in the high byte of the u16 flags at
 * *(child)+0x60, fire ov107_020c5af8(*child, 0x154, 0xb, *(child+0xc)), clear the +0x4e byte and
 * +0x2c, then register the handler. */
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov209_020d4a8c(int);
void func_ov209_020d4a0c(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 0xd, 1);
    ((struct hw60 *)(*(int *)child + 0x60))->hi &= ~0x40;
    func_ov107_020c5af8(*(int *)child, 0x154, 0xb, *(int *)(child + 0xc));
    *(signed char *)(child + 0x4e) = 0;
    *(int *)(child + 0x2c) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov209_020d4a8c);
}
