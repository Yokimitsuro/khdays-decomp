typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    int x;
    int y;
    int z;
    int w;
} Quat;

struct Sphere {
    VecFx32 centre;
    int radius;
};

struct Msg {
    u16 h[7];
};

struct W1 {
    int v;
};

struct Flags60 {
    u16 lo : 8;
    u16 hi : 8;
};

struct Flags17a {
    u8 bBit0 : 1;
    u8 bBit1 : 1;
};

struct State {
    void *pActor;
    char pad04[4];
    void *pTarget;
    int nAngle0c;
    int nAngle10;
    char pad14[4];
    VecFx32 vStep;
    char pad24[0x18];
    int nSpeed3c;
    char pad40[0x14];
    int nDistance54;
};

struct Node {
    void *pScene;
    struct State *pState;
    char pad08[0x18];
    signed char bSlot;
};

extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *ab);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *ab);
extern int VEC_DotProduct(VecFx32 *a, VecFx32 *b);
extern int func_01ff8d18(VecFx32 *out, VecFx32 *in);
extern void func_01ffa724(int scale, VecFx32 *in, VecFx32 *out);
extern void func_0202f384(VecFx32 *out, Quat *q, const VecFx32 *in);
extern void func_0202ed60(Quat *out, const VecFx32 *a, VecFx32 *b);
extern void func_0202f55c(Quat *out, int t, Quat *a, Quat *b);
extern void func_0202f4a4(Quat *out, Quat *in);
extern void func_0202f188(Quat *out, const VecFx32 *axis, int angle);
extern int func_020050b4(int x, int z);
extern void func_0203c9d0(void *srt, Quat *q);
extern void *func_ov107_020cab14(void *actor, int mode);
extern int func_ov107_020c8eb8(void *actor, struct Sphere *shape, void **out);
extern int func_ov107_020ca918(void *victim, void *a, void *b, int mode,
                               VecFx32 *push, int flags);
extern void func_ov107_020c5af8(void *actor, int id, u16 mode, VecFx32 *at);
extern void func_ov107_020c9264(void *actor, int a, int b);
extern void func_ov107_020c9ee8(void *obj, int a, int b);
extern void func_0203c634(struct Node *node, int slot, void *next);

extern const VecFx32 data_02042258;
extern const VecFx32 data_02042264;
extern const struct Msg data_ov131_020cef82;
extern void func_ov131_020cde38(void);

void func_ov131_020cd9a4(struct Node *node)
{
    struct State *st;
    VecFx32 vFwd;
    VecFx32 vToTarget;
    Quat quat;
    Quat delta;
    struct Sphere shape;
    void *aVictims[4];
    VecFx32 vPush;
    VecFx32 vImpact;
    struct Msg msg;
    VecFx32 vFacing;
    struct Msg tmpl;
    VecFx32 raw;
    void (*pfnHook)(void *, struct Msg *, int);
    int i;
    int hit;
    int angle;
    int nHits;

    st = node->pState;
    hit = 0;
    st->pTarget = func_ov107_020cab14(st->pActor, 0);
    if (st->pTarget == 0) {
        *(u8 *)((char *)st->pActor + 0x1c7) = 2;
        func_0203c634(node, node->bSlot, 0);
        return;
    }

    quat = *(Quat *)((char *)st->pActor + 0xa0);
    func_0202f384(&vFwd, &quat, &data_02042258);
    func_01ff8d18(&vFwd, &vFwd);
    VEC_Subtract((VecFx32 *)((char *)*(void **)((char *)st->pTarget + 0x1d8) + 4),
                 (VecFx32 *)((char *)*(void **)((char *)st->pActor + 0x38c) + 4),
                 &vToTarget);
    func_01ff8d18(&vToTarget, &vToTarget);
    func_0202ed60(&delta, &data_02042258, &vToTarget);
    if (VEC_DotProduct(&vFwd, &vToTarget) >= -0xa00) {
        func_0202f55c(&quat, (int)((((long long)(*(int *)((char *)node->pScene + 0x2c) * 0x1e) << 27) + 0x80000000) >> 32),
                      &quat, &delta);
        func_0202f4a4(&quat, &quat);
        func_0203c9d0((char *)st->pActor + 0xa0, &quat);
    }

    func_0202f384(&st->vStep, (Quat *)((char *)st->pActor + 0xa0), &data_02042258);
    func_01ff8d18(&st->vStep, &st->vStep);
    func_01ffa724(st->nSpeed3c, &st->vStep, &st->vStep);
    st->nDistance54 = st->nDistance54 + st->nSpeed3c;

    shape.centre = *(VecFx32 *)((char *)*(void **)((char *)st->pActor + 0x38c) + 4);
    VEC_Add(&shape.centre, &st->vStep, &shape.centre);
    shape.radius = 0x800;
    nHits = func_ov107_020c8eb8(st->pActor, &shape, aVictims);
    i = 0;
    if (nHits > 0) {
        tmpl = data_ov131_020cef82;
        do {
            VEC_Subtract((VecFx32 *)((char *)*(void **)((char *)aVictims[i] + 0x1d8) + 4),
                         &shape.centre, &vPush);
            vPush.y = 0;
            func_01ff8d18(&vPush, &vPush);
            func_01ffa724(0x800, &vPush, &vPush);
            if (func_ov107_020ca918(aVictims[i], st->pActor, st->pActor, 2,
                                    &vPush, 0) != 0) {
                msg = tmpl;
                func_01ffa724(shape.radius, &vToTarget, &vImpact);
                VEC_Add(&shape.centre, &vImpact, &vImpact);
                *(struct W1 *)&raw.x = *(struct W1 *)&vImpact.x;
                *(struct W1 *)&raw.y = *(struct W1 *)&vImpact.y;
                *(struct W1 *)&raw.z = *(struct W1 *)&vImpact.z;
                ((u8 *)&msg)[5] = (u8)(((u32)raw.x >> 16 & 0x7f) |
                                       ((u32)raw.x >> 24 & 0x80));
                ((u8 *)&msg)[6] = (u8)((u32)raw.x >> 8);
                ((u8 *)&msg)[7] = (u8)raw.x;
                ((u8 *)&msg)[8] = (u8)(((u32)raw.y >> 16 & 0x7f) |
                                       ((u32)raw.y >> 24 & 0x80));
                ((u8 *)&msg)[9] = (u8)((u32)raw.y >> 8);
                ((u8 *)&msg)[10] = (u8)raw.y;
                ((u8 *)&msg)[11] = (u8)(((u32)raw.z >> 16 & 0x7f) |
                                        ((u32)raw.z >> 24 & 0x80));
                ((u8 *)&msg)[12] = (u8)((u32)raw.z >> 8);
                ((u8 *)&msg)[13] = (u8)raw.z;
                pfnHook = *(void (**)(void *, struct Msg *, int))((char *)st->pActor + 0x24);
                if (pfnHook != 0) {
                    (*pfnHook)(st->pActor, &msg, 0xe);
                }
                hit = 1;
                func_ov107_020c5af8(st->pActor, 0x119, 5, &vImpact);
            }
            i++;
        } while (i < nHits);
    }

    if (hit == 0 && st->nDistance54 < 0x6000 &&
        ((struct Flags17a *)((char *)st->pActor + 0x17a))->bBit0 == 0 &&
        ((struct Flags17a *)((char *)st->pActor + 0x17a))->bBit1 == 0) {
        return;
    }

    func_0202f384(&vFacing, &quat, &data_02042258);
    vFacing.y = 0;
    if (func_01ff8d18(&vFacing, &vFacing) == 0) {
        vFacing = data_02042258;
    }
    angle = st->nAngle10 = func_020050b4(vFacing.x, vFacing.z);
    st->nAngle0c = angle;
    func_0202f188(&quat, &data_02042264, angle);
    func_0203c9d0((char *)st->pActor + 0xa0, &quat);
    func_ov107_020c9264(st->pActor, 5, 0);
    ((struct Flags60 *)((char *)st->pActor + 0x60))->hi =
        ((struct Flags60 *)((char *)st->pActor + 0x60))->hi & ~0x40;
    func_ov107_020c9ee8(*(void **)((char *)st->pActor + 0x3c8), 1, 0);
    func_0203c634(node, node->bSlot, (void *)func_ov131_020cde38);
}
