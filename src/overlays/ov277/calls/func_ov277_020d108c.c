/* Clear flag 0 then raise flags 0x82 in the high byte at (*child)+0x60, then register the handler. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov277_020d10f8(int);
struct node60_020d606c { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov277_020d108c(int param_1) {
    int child = *(int *)(param_1 + 4);
    ((struct node60_020d606c *)(*(int *)child + 0x60))->hi &= ~1;
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x82;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov277_020d10f8);
}
