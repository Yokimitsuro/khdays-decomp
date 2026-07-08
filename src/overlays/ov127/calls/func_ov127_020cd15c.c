extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_0203c634(int obj, int a, int cb);
extern void func_ov127_020cd1c0(void);

// Raise flag 0x40 in the node's hw60 high byte, switch to mode 4, reset the
// timer/flag fields, and advance the sub-state with the follow-up callback.
void func_ov127_020cd15c(int *this)
{
    int node = this[1];
    unsigned short *hw = (unsigned short *)(*(int *)node + 0x60);
    unsigned int u = *hw;
    *hw = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    func_ov107_020c9264(*(int *)node, 4, 0);
    *(int *)(node + 0x2c) = 0;
    *(signed char *)(node + 0x41) = 0;
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov127_020cd1c0);
}
