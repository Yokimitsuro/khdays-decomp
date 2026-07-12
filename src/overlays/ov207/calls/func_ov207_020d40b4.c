/* Enter reaction: clear flag 0 then raise flag 0x86 in the high byte at (*child)+0x60,
 * clear bit 0 in the low byte of [+8] of the two child slots at (*child)+0x3ac/+0x3b0,
 * run the ov107 effect (mode 0x49, data at +8), reset the sub-state byte +0x1c7 and dispatch. */
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern int func_0203c634(int a, int b, void *handler);
struct node60_020d0474 { unsigned short lo : 8; unsigned short hi : 8; };
struct lo8_020d0474 { unsigned f : 8; };
void func_ov207_020d40b4(int param_1) {
    int child = *(int *)(param_1 + 4);
    ((struct node60_020d0474 *)(*(int *)child + 0x60))->hi &= ~1;
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x86;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    {
        int c = *(int *)(*(int *)child + 0x3ac);
        ((struct lo8_020d0474 *)(c + 8))->f &= ~1;
    }
    {
        int c = *(int *)(*(int *)child + 0x3b0);
        ((struct lo8_020d0474 *)(c + 8))->f &= ~1;
    }
    func_ov107_020c5af8(*(int *)child, 0, 0x49, *(int *)(child + 8));
    *(signed char *)(*(int *)child + 0x1c7) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
