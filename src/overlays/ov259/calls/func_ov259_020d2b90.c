/* Move entry: the actor's +0x388 link clears, bit 7 of its +0x60 high byte is set and bit 0
 * cleared, the +0x384 shape is disarmed (bit 0 of its +8 byte), the +0xc velocity resets to zero
 * and the node's handler is cleared. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;

void func_ov259_020d2b90(int *node)
{
    int *state = (int *)node[1];

    *(int *)(*state + 0x388) = 0;
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
    ((B8 *)(*(int *)(*state + 0x384) + 8))->f &= ~1;
    *(Vec3 *)(state + 3) = data_02041dc8;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
