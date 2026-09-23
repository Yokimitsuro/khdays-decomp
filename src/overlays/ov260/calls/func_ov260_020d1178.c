/* Move entry: bit 0 of the actor's +0x60 high byte clears and bits 1 and 7 are set, the +0x388
 * shape is disarmed (bit 0 of its +8 byte), the +0x28 velocity resets to zero and the node moves
 * to 020d1228. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern void func_ov260_020d1228(void);

void func_ov260_020d1178(int *node)
{
    int *state = (int *)node[1];

    {
        int actor = *state;
        u16 hw = *(u16 *)(actor + 0x60);
        *(u16 *)(actor + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~1) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x82) << 0x18) >> 0x10);
    }
    ((B8 *)(*(int *)(*state + 0x388) + 8))->f &= ~1;
    *(Vec3 *)(state + 0xa) = data_02041dc8;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020d1228);
}
