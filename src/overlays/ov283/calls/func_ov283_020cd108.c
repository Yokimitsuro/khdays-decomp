/* Set flags 0x86 in the high byte of the u16 at obj+0x60, clear bit0 of the byte
 * at (obj+0x388)->+8, then dispatch. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov283_020cd170(void);
struct lo_020cd144 { unsigned int f : 8; };
void func_ov283_020cd108(int param_1) {
    int child = *(int *)(param_1 + 4);
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x86;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    ((struct lo_020cd144 *)(*(int *)(*(int *)child + 0x388) + 8))->f &= ~1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov283_020cd170);
}
