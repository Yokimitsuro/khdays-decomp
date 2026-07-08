extern void func_ov107_020c9264(int obj, int a, int b);
extern void func_ov107_020c9ee8(int obj, int a, int b);
extern void func_0203c634(int obj, int a, int cb);
extern void func_ov281_020cdc44(void);

// Switch to mode 7, kick the linked effect (node[0][0x3c0]), raise hw60 flag
// 0x40, reset the timer field (node[6]) and advance with the follow-up callback.
void func_ov281_020cdbd0(int *this)
{
    int node = this[1];
    func_ov107_020c9264(*(int *)node, 7, 0);
    func_ov107_020c9ee8(*(int *)(*(int *)node + 0x3c0), 1, 0);
    {
        unsigned short *hw = (unsigned short *)(*(int *)node + 0x60);
        unsigned int u = *hw;
        *hw = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    }
    *(int *)(node + 0x18) = 0;
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov281_020cdc44);
}
