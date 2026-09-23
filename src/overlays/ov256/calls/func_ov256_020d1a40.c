/* Move entry: bits 2-4 and bit 0 of the actor's +0x60 high byte are set, the +0x388 shape is armed
 * (bit 0 of its +8 byte), the +0x10 velocity resets to zero and the node moves to 020d1ae8. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern void func_ov256_020d1ae8(void);

void func_ov256_020d1a40(int *node)
{
    int *state = (int *)node[1];

    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x1c) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 1) << 0x18) >> 0x10);
    }
    ((B8 *)(*(int *)(*state + 0x388) + 8))->f |= 1;
    *(Vec3 *)(state + 4) = data_02041dc8;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020d1ae8);
}
