/* Raise flag 0x86 then clear flag 0 in the high byte at (*child)+0x60, reset +0x390 and
 * register the handler. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov213_020d2914(int);
struct node60_020d1d8c { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov213_020d289c(int param_1) {
    int child = *(int *)(param_1 + 4);
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x86;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    ((struct node60_020d1d8c *)(*(int *)child + 0x60))->hi &= ~1;
    *(int *)(*(int *)child + 0x390) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov213_020d2914);
}
