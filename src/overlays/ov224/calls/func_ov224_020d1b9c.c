/* Raise flags 0x86 in the high byte at (*child)+0x60, clear bit 0 in the low byte
 * of [+8] across the 5 child slots at (*child)+0x3ac, then register the handler. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov224_020d1c18(int);
struct lo8_020d1b80 { unsigned f : 8; };
void func_ov224_020d1b9c(int param_1) {
    int child = *(int *)(param_1 + 4);
    int i;
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x86;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    for (i = 0; i < 5; i++) {
        int c = ((int *)*(int *)child)[i + 0xeb];
        ((struct lo8_020d1b80 *)(c + 8))->f &= ~1;
    }
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov224_020d1c18);
}
