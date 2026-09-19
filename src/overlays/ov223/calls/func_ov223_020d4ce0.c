/* Ring charge tick of the ov223 enemy (variant 1): the +0x38c item's +0x3ac pool entry's +0x20
 * point is announced to the owner (ov107 c5c54) with bit 7 of the +0x60 high byte cleared, the
 * +0x20 target is data_02042258 turned by the item's +0xa0 pose, and the strike sweep (ov223
 * 442c, mode 0) runs with a segment from that point to the target of length 16.0 and radius
 * 0.5. The +0x3c timer accumulates the owner's rate; past 0x1200 it clears and the tick hands
 * over to func_ov223_020d4de8. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8, hi : 8; };
struct Ov223Segment { Vec3 p0; Vec3 p1; int nLength; int nRadius; };

extern void func_ov107_020c5c54(int owner, Vec3 *at);
extern void func_0202f384(Vec3 *out, const void *pose, const Vec3 *in);
extern int func_ov223_020d442c(int *node, int mode, struct Ov223Segment *seg);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042258;
extern void func_ov223_020d4de8(int *node);

void func_ov223_020d4ce0(int *node)
{
    int *state = (int *)node[1];
    struct Ov223Segment seg;
    Vec3 at;

    at = *(Vec3 *)(*(int *)(*(int *)(*(int *)(*state + 0x38c) + 0x3ac)) + 0x20);
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x80;
    func_ov107_020c5c54(*state, &at);
    func_0202f384((Vec3 *)(state + 8), (const void *)(*(int *)(*state + 0x38c) + 0xa0), &data_02042258);
    seg.p0 = at;
    seg.p1 = *(Vec3 *)(state + 8);
    seg.nLength = 0x10000;
    seg.nRadius = 0x800;
    func_ov223_020d442c(node, 0, &seg);
    state[0xf] += *(int *)(*node + 0x2c);
    if (state[0xf] <= 0x1200) {
        return;
    }
    state[0xf] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov223_020d4de8);
}
