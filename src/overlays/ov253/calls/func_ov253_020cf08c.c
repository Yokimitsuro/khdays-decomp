/* func_ov253_020cf08c -- roam entry: the +0x18 speed follows twice the frame step (30 / 15);
 * once bit 0 of the actor's +0x60 low byte is set a heading is drawn between the two
 * data_ov253_020d49b8 bounds picked by the +0x388 count modulo four, a point 8.0 plus a random
 * 8.0 away from the +0x384 item's +0xb0 along that heading is sent to the actor (020c5c54),
 * the +0x10 / +0x14 headings take another draw from the same bounds, the sub-state takes the
 * +0x1c9 byte and the node slot is released. */
typedef struct { int x, y, z; } Vec3;
struct hw60 { unsigned short lo : 8; unsigned short hi : 8; };
struct Ov253Bounds { int lo[1]; int hi[4]; };

extern int func_02023eb4(int scale);
extern void func_ov107_020c5c54(int actor, const Vec3 *pos);
extern void func_0203c634(int *node, int slot, void *cb);
extern const struct Ov253Bounds data_ov253_020d49b8;
extern const short data_0203d210[];

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}
static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

void func_ov253_020cf08c(int *node) {
    int *state = (int *)node[1];
    struct Ov253Bounds bounds;
    Vec3 pos;
    int idx;
    int angle;
    int lo;
    int span;
    int scale;
    int item;
    unsigned short sinIdx;

    state[6] = *(int *)(node[0] + 0x2c) * 0x1e / 0xf;
    if ((((struct hw60 *)(*state + 0x60))->lo & 1) == 0) {
        return;
    }
    bounds = data_ov253_020d49b8;
    idx = *(int *)(*state + 0x388) % 4;
    span = bounds.hi[idx];
    lo = bounds.lo[idx];
    span -= lo;
    angle = lo + func_02023eb4((span < 0 ? -span : span) + 1);
    scale = func_02023eb4(0x8001) + 0x8000;
    item = *(int *)(*state + 0x384);
    sinIdx = FX_RadToIdx(angle);
    pos = *(Vec3 *)(item + 0xb0);
    pos.x += FX_Mul(data_0203d210[(sinIdx >> 4) << 1], scale);
    pos.z += FX_Mul(data_0203d210[((sinIdx >> 4) << 1) + 1], scale);
    func_ov107_020c5c54(*state, &pos);
    state[4] = state[5] = lo + func_02023eb4((span < 0 ? -span : span) + 1);
    *(signed char *)(*state + 0x1c7) = *(signed char *)(*state + 0x100 + 0xc9);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
