/* Enter tick of the ov255 partner's state: bits 2, 3 and 7 of the owner's +0x60 high byte clear
 * and bit 1 is raised, the low byte of its +0x38c rig's +8 word gets bit 0, +0x18 becomes 0.25,
 * +0x1c and +0x14 clear, effect 2 is spawned at the origin and the tick hands over to
 * func_ov255_020d1ed8. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
struct hw60 { u16 lo : 8, hi : 8; };
struct Word8 { unsigned int lo : 8; };

extern void func_ov107_020c0b90(int owner, int id, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;
extern void func_ov255_020d1ed8(int *node);

void func_ov255_020d1df8(int *node)
{
    int *obj = (int *)node[1];
    u16 hw;

    ((struct hw60 *)(*obj + 0x60))->hi &= ~0x8c;
    hw = *(u16 *)(*obj + 0x60);
    *(u16 *)(*obj + 0x60) = (hw & ~0xff00) |
        ((((((unsigned int)hw << 0x10) >> 0x18) | 2) << 0x18) >> 0x10);
    ((struct Word8 *)(*(int *)(*obj + 0x38c) + 8))->lo |= 1;
    obj[6] = 0x400;
    obj[7] = 0;
    obj[5] = 0;
    func_ov107_020c0b90(*obj, 2, data_02041dc8, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov255_020d1ed8);
}
