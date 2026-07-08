struct lobyte { unsigned int b : 8; };

extern void func_0203c634(int obj, int slot, int cb);
extern void func_ov140_020d0654(void);
extern void func_ov140_020d03a8(void);
extern void func_ov140_020d0560(void);

// Enter the aim state: reset the object's sub-state bytes (0x1c6=0, 0x1c7=-1),
// clear the linked flag bit (node[0][0x388][8] bit0), cache the pose/target
// pointers into node[0x48..0x50], raise hw60 flags 6, and install the three
// state callbacks in slots 1/0/2.
void func_ov140_020d02d4(int *this)
{
    int node = this[1];
    *(signed char *)(*(int *)node + 0x1c6) = 0;
    *(signed char *)(*(int *)node + 0x1c7) = -1;
    ((struct lobyte *)(*(int *)(*(int *)node + 0x388) + 8))->b &= ~1;
    *(int *)(node + 0x48) = *(int *)node + 0xb0;
    *(int *)(node + 0x4c) = *(int *)node + 0x74;
    *(int *)(node + 0x50) = *(int *)(*(int *)node + 0x384) + 0xad;
    {
        unsigned short *hw = (unsigned short *)(*(int *)node + 0x60);
        unsigned int u = *hw;
        *hw = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));
    }
    func_0203c634((int)this, 1, (int)&func_ov140_020d0654);
    func_0203c634((int)this, 0, (int)&func_ov140_020d03a8);
    func_0203c634((int)this, 2, (int)&func_ov140_020d0560);
}
