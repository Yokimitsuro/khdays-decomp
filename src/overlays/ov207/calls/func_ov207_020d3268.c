/* Reset the timer (+0x24) and phase byte (+0x52), raise flag 0x40 in the high byte at
 * (*child)+0x60, play the anim (ov107 mode 0xd) and register the handler. */
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov207_020d32c8(int);
void func_ov207_020d3268(int param_1) {
    int child = *(int *)(param_1 + 4);
    *(int *)(child + 0x24) = 0;
    *(signed char *)(child + 0x52) = 0;
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x40;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    func_ov107_020c9264(*(int *)child, 0xd, 0);
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov207_020d32c8);
}
