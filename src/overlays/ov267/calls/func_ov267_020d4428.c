/* Accumulate the owner rate (+0x2c) into the timer at (child)+0x40; once it reaches 0xd48,
 * run the sub-update (020ce404), clear flag 0 then raise flag 0x80 in the high byte at
 * (*child)+0x60, reset the sub-state byte (+0x1c7) and dispatch with no handler. */
extern void func_ov267_020d2020(int);
extern int func_0203c634(int a, int b, void *handler);
struct node60_020d080c { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov267_020d4428(int param_1) {
    int child = *(int *)(param_1 + 4);
    int t = *(int *)(child + 0x40) + *(int *)(*(int *)param_1 + 0x2c);
    *(int *)(child + 0x40) = t;
    if (t < 0xd48) return;
    func_ov267_020d2020(child);
    ((struct node60_020d080c *)(*(int *)child + 0x60))->hi &= ~1;
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x80;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    *(signed char *)(*(int *)child + 0x1c7) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)0);
}
