/* Charge step of an ov150 enemy action: push anything caught in front and end
 * the action, otherwise steer the heading toward the target and keep
 * accelerating until the charged distance runs out.
 *
 * There are three exits and each one announces itself with a fourteen byte
 * message: a push landed on a victim, the owner dropped the second flag, or the
 * charge covered more than 0x14000. The message blocks use the packed position
 * idiom of ov131 020cd9a4 and ov281 020cc440: copy a seven halfword template,
 * then write each coordinate as three bytes, the top one keeping bit 7 of the
 * high byte and the low seven bits of the middle byte. Each block needs its own
 * buffer and its own raw vector, and the struct W1 copy is what forces the real
 * store; sharing them collapses the frame.
 *
 * The heading pick is the ov137 020cc9e0 idiom: 0x28be60db9391 is 65536/(2*PI)
 * in .32 and the pair at data_0203d210 is sin and cos. The random spread is
 * computed into its own variable and the atan2 result into another before they
 * are summed, which is what keeps the fresh call result in the leading slot.
 *
 * The vertical step divides into two arms: without the first flag the fall is a
 * flat 0x80 per frame, with it the remaining vertical speed is scaled and the
 * forward speed decays, both inside that same arm.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

struct Msg {
    u16 h[7];
};

struct W1 {
    int v;
};

struct Flags17a {
    u8 bBit0 : 1;
    u8 bBit1 : 1;
};

struct State {
    void *pActor;
    VecFx32 *pPoint04;
    VecFx32 vStep08;
    VecFx32 vDir14;
    int nSpeed20;
    int nDistance24;
};

struct Node {
    void *pScene;
    struct State *pState;
    char pad08[0x18];
    signed char bSlot;
};

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern int VEC_Mag(const VecFx32 *v);
extern int func_01ff8d18(VecFx32 *out, VecFx32 *in);
extern void func_01ffa724(int scale, VecFx32 *in, VecFx32 *out);
extern int func_020050b4(int x, int z);
extern int func_02023eb4();
extern void *func_ov107_020cab14(void *actor, int mode);
extern int func_ov107_020c8eb8(void *a, VecFx32 *at, void **out);
extern int func_ov107_020ca918(void *victim, void *actor, void *owner, int mode,
                               VecFx32 *push, int flags);
extern void func_ov107_020c5af8(void *actor, int id, u16 mode, VecFx32 *at);
extern void func_0203c634(struct Node *node, int slot, void *next);

extern const struct Msg data_ov150_020d2580;
extern const struct Msg data_ov150_020d258e;
extern const struct Msg data_ov150_020d25aa;
extern const short data_0203d210[];

static inline int Ov150FxMul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov150_020d1d5c(struct Node *node)
{
    void *pActor;
    struct State *st;
    void *aVictims[4];
    VecFx32 vPush;
    struct Msg msg1;
    VecFx32 vToTarget;
    VecFx32 vFacing;
    VecFx32 vSum;
    struct Msg msg2;
    struct Msg msg3;
    VecFx32 raw1;
    VecFx32 raw2;
    VecFx32 raw3;
    void (*pfnHook)(void *, struct Msg *, int);
    VecFx32 *pPoint;
    void *pTarget;
    int i;
    int nHits;
    int off;
    int angle;
    long long m;
    int fb;
    int t;

    st = node->pState;
    pActor = st->pActor;
    nHits = func_ov107_020c8eb8(*(void **)((char *)pActor + 0x38c),
                                (VecFx32 *)((char *)pActor + 0x74), aVictims);
    i = 0;
    if (nHits > 0) {
        do {
            VEC_Subtract((VecFx32 *)((char *)aVictims[i] + 0x74),
                         (VecFx32 *)((char *)pActor + 0x74), &vPush);
            vPush.y = 0;
            func_01ff8d18(&vPush, &vPush);
            func_01ffa724(0x800, &vPush, &vPush);
            if (func_ov107_020ca918(aVictims[i], st->pActor,
                                    *(void **)((char *)st->pActor + 0x38c), 0,
                                    &vPush, 0) != 0) {
                msg1 = data_ov150_020d258e;
                pPoint = st->pPoint04;
                *(struct W1 *)&raw1.x = *(struct W1 *)&pPoint->x;
                ((u8 *)&msg1)[5] = (u8)(((u32)raw1.x >> 16 & 0x7f) |
                                       ((u32)raw1.x >> 24 & 0x80));
                ((u8 *)&msg1)[6] = (u8)((u32)raw1.x >> 8);
                ((u8 *)&msg1)[7] = (u8)raw1.x;
                *(struct W1 *)&raw1.y = *(struct W1 *)&pPoint->y;
                ((u8 *)&msg1)[8] = (u8)(((u32)raw1.y >> 16 & 0x7f) |
                                       ((u32)raw1.y >> 24 & 0x80));
                ((u8 *)&msg1)[9] = (u8)((u32)raw1.y >> 8);
                ((u8 *)&msg1)[10] = (u8)raw1.y;
                *(struct W1 *)&raw1.z = *(struct W1 *)&pPoint->z;
                ((u8 *)&msg1)[11] = (u8)(((u32)raw1.z >> 16 & 0x7f) |
                                        ((u32)raw1.z >> 24 & 0x80));
                ((u8 *)&msg1)[12] = (u8)((u32)raw1.z >> 8);
                ((u8 *)&msg1)[13] = (u8)raw1.z;
                pfnHook = *(void (**)(void *, struct Msg *, int))
                    ((char *)st->pActor + 0x24);
                if (pfnHook != 0) {
                    (*pfnHook)(st->pActor, &msg1, 0xe);
                }
                func_ov107_020c5af8(st->pActor, 0x14e, 5, st->pPoint04);
                *(u8 *)((char *)st->pActor + 0x1c7) = 0;
                func_0203c634(node, node->bSlot, 0);
                return;
            }
            i++;
        } while (i < nHits);
    }

    if (((struct Flags17a *)((char *)st->pActor + 0x17a))->bBit0 != 0) {
        pTarget = func_ov107_020cab14(st->pActor, 0);
        if (pTarget != 0) {
            VEC_Subtract((VecFx32 *)((char *)pTarget + 0x74),
                         (VecFx32 *)((char *)pActor + 0x74), &vToTarget);
            vToTarget.y = 0;
            vFacing = st->vDir14;
            vFacing.y = 0;
            func_01ff8d18(&vToTarget, &vToTarget);
            func_01ff8d18(&vFacing, &vFacing);
            if (VEC_DotProduct(&vToTarget, &vFacing) > 0x800) {
                VEC_Add(&vToTarget, &vFacing, &vSum);
                off = func_02023eb4(0x10c1) - 0x860;
                angle = func_020050b4(vSum.x, vSum.z);
                angle = angle + off;
                t = (unsigned short)(((long long)angle * 0x28be60db9391LL
                                      + 0x80000000000LL) >> 44) >> 4;
                st->vDir14.x = data_0203d210[t * 2];
                st->vDir14.z = data_0203d210[t * 2 + 1];
            }
        }
    }

    st->vStep08.x = (int)(((long long)st->vDir14.x * st->nSpeed20
                           + 0x800) >> 12);
    st->vStep08.z = (int)(((long long)st->vDir14.z * st->nSpeed20
                           + 0x800) >> 12);

    if (((struct Flags17a *)((char *)st->pActor + 0x17a))->bBit0 == 0) {
        st->vStep08.y = st->vStep08.y - 0x80;
    } else {
        st->vStep08.y = -Ov150FxMul(st->vStep08.y, 0xd00);
        st->nSpeed20 = st->nSpeed20 + (-st->nSpeed20) / 20;
    }

    if (((struct Flags17a *)((char *)st->pActor + 0x17a))->bBit1 != 0) {
        msg2 = data_ov150_020d2580;
        pPoint = st->pPoint04;
        *(struct W1 *)&raw2.x = *(struct W1 *)&pPoint->x;
        ((u8 *)&msg2)[5] = (u8)(((u32)raw2.x >> 16 & 0x7f) |
                               ((u32)raw2.x >> 24 & 0x80));
        ((u8 *)&msg2)[6] = (u8)((u32)raw2.x >> 8);
        ((u8 *)&msg2)[7] = (u8)raw2.x;
        *(struct W1 *)&raw2.y = *(struct W1 *)&pPoint->y;
        ((u8 *)&msg2)[8] = (u8)(((u32)raw2.y >> 16 & 0x7f) |
                               ((u32)raw2.y >> 24 & 0x80));
        ((u8 *)&msg2)[9] = (u8)((u32)raw2.y >> 8);
        ((u8 *)&msg2)[10] = (u8)raw2.y;
        *(struct W1 *)&raw2.z = *(struct W1 *)&pPoint->z;
        ((u8 *)&msg2)[11] = (u8)(((u32)raw2.z >> 16 & 0x7f) |
                                ((u32)raw2.z >> 24 & 0x80));
        ((u8 *)&msg2)[12] = (u8)((u32)raw2.z >> 8);
        ((u8 *)&msg2)[13] = (u8)raw2.z;
        pfnHook = *(void (**)(void *, struct Msg *, int))
            ((char *)st->pActor + 0x24);
        if (pfnHook != 0) {
            (*pfnHook)(st->pActor, &msg2, 0xe);
        }
        func_ov107_020c5af8(st->pActor, 0x14e, 6, st->pPoint04);
        *(u8 *)((char *)st->pActor + 0x1c7) = 0;
        func_0203c634(node, node->bSlot, 0);
        return;
    }

    st->nDistance24 = st->nDistance24 + VEC_Mag(&st->vStep08);
    if (st->nDistance24 <= 0x14000) {
        return;
    }

    msg3 = data_ov150_020d25aa;
    pPoint = st->pPoint04;
    *(struct W1 *)&raw3.x = *(struct W1 *)&pPoint->x;
    ((u8 *)&msg3)[5] = (u8)(((u32)raw3.x >> 16 & 0x7f) |
                           ((u32)raw3.x >> 24 & 0x80));
    ((u8 *)&msg3)[6] = (u8)((u32)raw3.x >> 8);
    ((u8 *)&msg3)[7] = (u8)raw3.x;
    *(struct W1 *)&raw3.y = *(struct W1 *)&pPoint->y;
    ((u8 *)&msg3)[8] = (u8)(((u32)raw3.y >> 16 & 0x7f) |
                           ((u32)raw3.y >> 24 & 0x80));
    ((u8 *)&msg3)[9] = (u8)((u32)raw3.y >> 8);
    ((u8 *)&msg3)[10] = (u8)raw3.y;
    *(struct W1 *)&raw3.z = *(struct W1 *)&pPoint->z;
    ((u8 *)&msg3)[11] = (u8)(((u32)raw3.z >> 16 & 0x7f) |
                            ((u32)raw3.z >> 24 & 0x80));
    ((u8 *)&msg3)[12] = (u8)((u32)raw3.z >> 8);
    ((u8 *)&msg3)[13] = (u8)raw3.z;
    pfnHook = *(void (**)(void *, struct Msg *, int))
        ((char *)st->pActor + 0x24);
    if (pfnHook != 0) {
        (*pfnHook)(st->pActor, &msg3, 0xe);
    }
    *(u8 *)((char *)st->pActor + 0x1c7) = 0;
    func_0203c634(node, node->bSlot, 0);
}
