/* Clear bits 0x9c in the high byte of the u16 flags at *(child)+0x60, clear bits 3 of the u16 at
 * *(child)+0x1ae, set +8/+0x10/+0x14 = 0 and +0xc = -0x300, then register the handler. */
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov277_020d11a4(int);
void func_ov277_020d1130(int param_1) {
    int child = *(int *)(param_1 + 4);
    ((struct hw60 *)(*(int *)child + 0x60))->hi &= ~0x9c;
    *(unsigned short *)(*(int *)child + 0x1ae) &= ~3;
    *(int *)(child + 8) = 0;
    *(int *)(child + 0xc) = -0x300;
    *(int *)(child + 0x10) = 0;
    *(int *)(child + 0x14) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov277_020d11a4);
}
