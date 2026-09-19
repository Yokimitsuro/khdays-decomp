/* func_ov253_020d3ff4 -- stop entry: raises bits 1 and 7 and clears bit 0 of the actor's +0x60
 * high byte, zeroes the state's +8 vector and moves the node to 020d407c. */
typedef struct { int x, y, z; } Vec3;
typedef unsigned short u16;

extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern void func_ov253_020d407c(void);

void func_ov253_020d3ff4(int *node) {
    int *state = (int *)node[1];

    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x82) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~1) << 0x18) >> 0x10);
    }
    *(Vec3 *)(state + 2) = data_02041dc8;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020d407c);
}
