/* Accumulate the owner rate (+0x2c) into the timer at (child)+0x28; once it reaches 0x6ee,
 * clear bits 0x82 in the high byte of the u16 flags at *(child)+0x60 and dispatch via
 * ov231_020cd094 with the ov231_020cd88c handler. */
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
extern int func_ov265_020d0ce8(int a, int b, int c, int d, void *e);
extern void func_ov265_020d14e0(int);
void func_ov265_020d1460(int param_1) {
    int child = *(int *)(param_1 + 4);
    int t = *(int *)(child + 0x28) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x28) = t;
    if (t < 0x6ee) return;
    ((struct hw60 *)(*(int *)child + 0x60))->hi &= ~0x82;
    func_ov265_020d0ce8(param_1, 0, 0, 0, (void *)&func_ov265_020d14e0);
}
