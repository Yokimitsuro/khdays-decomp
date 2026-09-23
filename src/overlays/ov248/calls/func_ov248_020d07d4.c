/* Entry of the ov248 actor's hit move: bit 0 of the owner's +0x60 high byte is set and bit 7 cleared,
 * the owner plays effect 1 in place and cue 0x146 (13) on the +8 target, the +0x1c flag and the +0x18
 * clock reset, and brain slot +0x20 runs 020d08a0. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int owner, int cue, int kind, void *target);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov248_020d08a0(void);
extern const Vec3 data_02041dc8;

void func_ov248_020d07d4(int *node)
{
    int *state = (int *)node[1];

    {
        u16 hw = *(u16 *)(*state + 0x60);

        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);

        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x80) << 0x18) >> 0x10);
    }
    func_ov107_020c0b90(*state, 1, data_02041dc8, 1);
    func_ov107_020c5af8(*state, 0x146, 0xd, (void *)state[2]);
    *((unsigned char *)state + 0x1c) = 0;
    state[6] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov248_020d08a0);
}
