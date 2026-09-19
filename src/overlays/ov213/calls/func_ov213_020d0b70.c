/* Raise flags 0x86 in the high byte at (*child)+0x60, then clear bit 0 of that same high byte
 * and bit 0 of the (*child)+0x394 word, then register the 020d0bec handler. */
typedef unsigned short u16;
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov213_020d0bec(int);
void func_ov213_020d0b70(int param_1) {
    int child = *(int *)(param_1 + 4);
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x86;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    {
        int actor = *(int *)child;
        u16 hw = *(u16 *)(actor + 0x60);
        *(u16 *)(actor + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~1) << 0x18) >> 0x10);
    }
    *(int *)(*(int *)child + 0x394) &= ~1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov213_020d0bec);
}
