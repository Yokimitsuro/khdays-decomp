/* Accumulate the owner rate (+0x2c) into the timer at (child)+0x2c; once it reaches 0xd48,
 * raise flag 0x80 and clear flag 0 in the high byte at (*child)+0x60, reset the sub-state
 * byte (+0x1c7) and dispatch with no handler. */
extern int func_0203c634(int a, int b, void *handler);
struct node60_020d362c { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov208_020d362c(int param_1) {
    int child = *(int *)(param_1 + 4);
    int t = *(int *)(child + 0x2c) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x2c) = t;
    if (t < 0xd48) return;
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x80;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    ((struct node60_020d362c *)(*(int *)child + 0x60))->hi &= ~1;
    *(signed char *)(*(int *)child + 0x1c7) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
