/* Move entry: bits 2 and 0 of the actor's +0x60 high byte are set, the +0x38c shape is disarmed
 * (bit 0 of its +8 byte), the +0xc velocity resets to zero and the node moves to 020d2254. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern void func_ov259_020d2254(void);

void func_ov259_020d21ac(int *node)
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
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    ((B8 *)(*(int *)(*state + 0x38c) + 8))->f &= ~1;
    *(Vec3 *)(state + 3) = data_02041dc8;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020d2254);
}
