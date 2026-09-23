/* Entry of the ov248 actor's follow move: the owner's +0x398 position is kept in +0xc, bit 7 of the
 * owner's +0x60 high byte is set and bit 0 cleared, then brain slot +0x20 runs 020d079c. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov248_020d079c(void);

void func_ov248_020d0714(int *node)
{
    int *state = (int *)node[1];

    *(Vec3 *)(state + 3) = *(Vec3 *)(*state + 0x398);
    {
        u16 hw = *(u16 *)(*state + 0x60);

        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x80) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);

        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~1) << 0x18) >> 0x10);
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov248_020d079c);
}
