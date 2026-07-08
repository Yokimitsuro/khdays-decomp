struct lobyte { unsigned int b : 8; };

extern void func_0203c634(int obj, int a, int cb);
extern void func_ov135_020d07e0(void);

// Raise flags 0x86 in the node's hw60 high byte, clear bit0 of the linked
// object's status byte (node[0][0x38c][8]) and of the local flag byte
// (node+0x42), then advance the sub-state with the follow-up callback.
void func_ov135_020d076c(int *this)
{
    int node = this[1];
    unsigned short *hw = (unsigned short *)(*(int *)node + 0x60);
    unsigned int u = *hw;
    *hw = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10));
    ((struct lobyte *)(*(int *)(*(int *)node + 0x38c) + 8))->b &= ~1;
    *(unsigned char *)((int)node + 0x42) &= ~1;
    func_0203c634((int)this, *(signed char *)((int)this + 0x20), (int)&func_ov135_020d07e0);
}
