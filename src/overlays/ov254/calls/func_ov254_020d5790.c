/* Raise flag 0x80 and clear flag 0 in the high byte at (*child)+0x60, then register the handler. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov254_020d57fc(int);
struct node60_020d40ac { unsigned short lo : 8; unsigned short hi : 8; };
void func_ov254_020d5790(int param_1) {
    int child = *(int *)(param_1 + 4);
    {
        unsigned short *p = (unsigned short *)(*(int *)child + 0x60);
        unsigned int hi = ((unsigned int)*p << 0x10) >> 0x18;
        hi |= 0x80;
        *p = (unsigned short)((*p & ~0xff00) | ((hi << 0x18) >> 16));
    }
    ((struct node60_020d40ac *)(*(int *)child + 0x60))->hi &= ~1;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov254_020d57fc);
}
