/* Play the anim (ov107 mode 0xf,1), clear bit 0x40 in the high byte of the u16 flags at
 * *(child)+0x60, fire ov107_020c5af8(*child, 0x116, 0xf, *(child+8)), clear the +0x50 byte and
 * +0x24, then register the handler. */
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov207_020d3680(int);
void func_ov207_020d35fc(int param_1) {
    int child = *(int *)(param_1 + 4);
    func_ov107_020c9264(*(int *)child, 0xf, 1);
    ((struct hw60 *)(*(int *)child + 0x60))->hi &= ~0x40;
    func_ov107_020c5af8(*(int *)child, 0x116, 0xf, *(int *)(child + 8));
    *(signed char *)(child + 0x50) = 0;
    *(int *)(child + 0x24) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov207_020d3680);
}
