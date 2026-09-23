/* Move entry: the actor's +0x38c link clears, bit 7 of its +0x60 high byte is set and bit 0
 * cleared, the +0x388 shape is disarmed and the node moves to 020d2604. */
typedef unsigned short u16;
typedef struct { unsigned f : 8; } B8;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov254_020d2604(void);

void func_ov254_020d2564(int *node)
{
    int *state = (int *)node[1];

    *(int *)(*state + 0x38c) = 0;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x80) << 0x18) >> 0x10);
    }
    {
        int actor = *state;
        u16 hw = *(u16 *)(actor + 0x60);
        *(u16 *)(actor + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~1) << 0x18) >> 0x10);
    }
    ((B8 *)(*(int *)(*state + 0x388) + 8))->f &= ~1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020d2604);
}
