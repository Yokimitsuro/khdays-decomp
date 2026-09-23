/* Tail-lash tick: the segment of the owner's +0x384 part (+0x78), moved to 0.19 above the actor's
 * +0x74 point and lengthened by 2.56, is swept over the actor list on behalf of the +0x38c owner. The
 * first entity that accepts a 0.125 push away from the part's +4 point, lifted by 0.375 (kind 1),
 * gets effect 0xb at its +0x74 point and pose 0 is requested (the original also scales and adds two
 * uninitialised scratch vectors there, whose result is unused). Otherwise the +0x24 timer
 * accumulates the frame rate and past 0.6, or once blocked (+0x17a bit 1), pose 0 is requested. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;
struct Bits17a { unsigned char b0 : 1, b1 : 1; };

extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const void *a, const void *b, void *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov259_020d2d3c(int *node)
{
    int *state = (int *)node[1];
    Segment seg;
    Vec3 pos;
    int hits[4];
    Vec3 push;
    Vec3 b;
    Vec3 a;
    int i;
    int n;

    seg = *(Segment *)(**(int **)(*state + 0x384) + 0x78);
    pos = *(Vec3 *)(*state + 0x74);
    pos.y += 0x300;
    seg.p0 = pos;
    seg.nLength += 0x2900;
    n = func_ov107_020c8f44(*(int *)(*state + 0x38c), &seg, hits);
    for (i = 0; i < n; i++) {
        VEC_Subtract((void *)(hits[i] + 0x74), (void *)(**(int **)(*state + 0x384) + 4), &push);
        func_01ff8d18(&push, &push);
        func_01ffa724(0x200, &push, &push);
        push.y = 0x600;
        if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x38c), 1, &push, 0) == 0) {
            continue;
        }
        func_01ffa724(seg.nRadius, &a, &a);
        VEC_Add(&a, &b, &a);
        func_ov107_020c0b90(*(int *)(*state + 0x38c), 0xb, *(Vec3 *)(hits[i] + 0x74), 0);
        *(u8 *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[9] += *(int *)(node[0] + 0x2c);
    if (state[9] > 0x990) {
        *(u8 *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (((struct Bits17a *)(*state + 0x17a))->b1 == 0) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
