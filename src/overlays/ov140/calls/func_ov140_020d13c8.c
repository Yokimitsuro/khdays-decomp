struct b1 { unsigned char b : 1; };

extern void func_ov107_020c9ee8(int a, int b, int c, unsigned int d);
extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203c634(int obj, int a, int cb);
extern void func_ov140_020d145c(void);

// Only act if either ready flag (obj[0x17a]/obj[0x17c] bit0) is set. Raise flag
// 0x40 in hw60, kick the linked effect (obj[0x390]) with the new flags, switch to
// mode 8, clear node[0x55] and advance with the follow-up callback.
void func_ov140_020d13c8(int *this)
{
    int node = this[1];
    int obj = *(int *)node;
    if (((struct b1 *)(obj + 0x17a))->b == 0 && ((struct b1 *)(obj + 0x17c))->b == 0) {
        return;
    }
    {
        unsigned short *hw = (unsigned short *)(obj + 0x60);
        unsigned int u = *hw;
        unsigned int flags = (u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
        *hw = (unsigned short)flags;
        func_ov107_020c9ee8(*(int *)(*(int *)node + 0x390), 3, 0, flags);
    }
    func_ov107_020c9264(*(int *)node, 8, 0);
    *(signed char *)(node + 0x55) = 0;
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov140_020d145c);
}
