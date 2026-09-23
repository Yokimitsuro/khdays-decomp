/* Enter the ov258 held item's flight: bits 2 and 0 of the +0x60 high byte are set and bit 7 cleared,
 * and the brain waits on 020d029c. */
typedef unsigned short u16;

extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov258_020d029c(void);

void func_ov258_020d020c(int *node)
{
    int *state = (int *)node[1];

    {
        u16 hw = *(u16 *)(*state + 0x60);

        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 4) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);

        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x80) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);

        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov258_020d029c);
}
