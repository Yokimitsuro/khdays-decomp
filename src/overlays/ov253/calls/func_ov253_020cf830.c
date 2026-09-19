/* func_ov253_020cf830 -- turn entry: the +0x18 speed follows twice the frame step (30 / 15) and
 * the +0x1c timer runs down; once expired a heading is drawn between the two
 * data_ov253_020d49cc bounds picked by the +0x388 count modulo four, a point 8.0 plus a random
 * 16.0 away from the +0x384 item's +0xb0 along that heading is sent to the actor (020c5c54),
 * bits 1 and 7 of the +0x60 high byte clear, pose 2 plays, the +0x10 / +0x14 headings take
 * another draw from the same bounds plus 3.14, the timer and +0x30 latch clear, reaction
 * 0x16c/7 fires at the +4 anchor and the node moves to 020cfa44. */
typedef struct { int x, y, z; } Vec3;
typedef unsigned short u16;
struct Ov253Bounds { int lo[1]; int hi[4]; };

extern int func_02023eb4(int scale);
extern void func_ov107_020c5c54(int actor, const Vec3 *pos);
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);
extern const struct Ov253Bounds data_ov253_020d49cc;
extern const short data_0203d210[];
extern void func_ov253_020cfa44(void);

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}
static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

void func_ov253_020cf830(int *node) {
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
    state[7] -= *(int *)(node[0] + 0x2c);
    if (state[7] > 0) {
        return;
    }
    bounds = data_ov253_020d49cc;
    idx = *(int *)(*state + 0x388) % 4;
    span = bounds.hi[idx];
    lo = bounds.lo[idx];
    span -= lo;
    angle = lo + func_02023eb4((span < 0 ? -span : span) + 1);
    scale = func_02023eb4(0x10001) + 0x8000;
    item = *(int *)(*state + 0x384);
    sinIdx = FX_RadToIdx(angle);
    pos = *(Vec3 *)(item + 0xb0);
    pos.x += FX_Mul(data_0203d210[(sinIdx >> 4) << 1], scale);
    pos.z += FX_Mul(data_0203d210[((sinIdx >> 4) << 1) + 1], scale);
    func_ov107_020c5c54(*state, &pos);
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(unsigned short)((((unsigned int)hw << 0x10) >> 0x18) & ~0x82) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*state, 2, 0);
    state[4] = state[5] = lo + func_02023eb4((span < 0 ? -span : span) + 1) + 0x3244;
    state[7] = 0;
    *((unsigned char *)state + 0x30) = 0;
    func_ov107_020c5af8(*state, 0x16c, 7, (void *)state[1]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020cfa44);
}
