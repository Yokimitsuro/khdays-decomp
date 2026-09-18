/*
 * func_ov135_020d116c -- burst attack tick of the ov134 enemy (and its byte-identical twins).
 *
 * The scene delta accumulates in the +0x30 timer. At 0x999 the actor's message hook receives the
 * 14-byte template at +0xe of the overlay data with the +0x38 point packed as three
 * sign-plus-magnitude 24-bit components (flag bit 0, once). At 0xc38 reaction 0x11c mode 4 fires
 * at the +0x3c point (flag bit 1, once). From 0xaaa on, every frame sweeps twice (forward by
 * 0x1000 then 0x2000 along the actor's +0xa0 matrix) a 0x800 sphere ahead of the +0x3c point;
 * each swept entity whose +0x1b4 id bit is clear in the +0x41 mask is pushed away by 0x600 on
 * the ground plane through the ov107 checker, and on acceptance the +0x0 template is broadcast
 * with the entity's +0x74 position (raised by 0x800), the id bit is set and reaction 0x11c mode 5
 * fires there. When the +4 item's +0xad flag is clear the actor plays animation 1 and the tick
 * hands off to the recovery state.
 *
 * Codegen notes (see func_ov120_020cd2fc): the working message is declared before the template
 * (msg above tmpl in the frame, the copy loop then keeps `subs` after the stores); the mirrored
 * position is a wrapped-value copy (FxVec) so the unread stack copy survives; the two-pass
 * counter is a signed char; the entity id at +0x1b4 is read unsigned.
 */
typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { int x, y, z; };
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
struct Ov134AreaMsg { u16 h[7]; };
struct Ov107SweepQuery { struct Vec3 vPos; int nRadius; };

struct Ov134Actor {
    char pad000[0x24];
    void (*pMsgHook24)(struct Ov134Actor *actor, void *msg, int len);
    char pad028[0x78];
    int aMatrixA0[9];
};

struct Ov134ActionState {
    struct Ov134Actor *pOwner;   /* +0x00 */
    char *pItem04;               /* +0x04 */
    char pad008[0x28];
    int nElapsed30;              /* +0x30 */
    char pad034[4];
    struct Vec3 *pPoint38;       /* +0x38 */
    struct Vec3 *pPoint3c;       /* +0x3c */
    u8 bFlags40;                 /* +0x40 */
    u8 bHitMask41;               /* +0x41 */
};

struct SceneFrameClock {
    char pad00[0x2c];
    int nDelta2c;
};

struct Ov134ActionNode {
    struct SceneFrameClock *pClock;
    struct Ov134ActionState *pState;
    char pad08[0x18];
    signed char bSlot;
};

extern struct Ov134AreaMsg data_ov135_020d1be2;
extern struct Ov134AreaMsg data_ov135_020d1bd4;
extern struct Vec3 data_02042258;

extern void func_0202f384(struct Vec3 *dst, int *mtx, struct Vec3 *src);
extern int func_01ff8d18(struct Vec3 *v, struct Vec3 *unit);
extern void func_01ffa724(int scale, void *src, void *dst);
extern void VEC_Add(void *a, void *b, void *out);
extern int func_ov107_020c8eb8(struct Ov134Actor *owner, void *query, void *results);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_ov107_020ca918(int ent, struct Ov134Actor *a, struct Ov134Actor *b, int mode,
                               void *dir, int flag);
extern void func_ov107_020c5af8(struct Ov134Actor *owner, int a, int id, void *anchor);
extern void func_ov107_020c9264(struct Ov134Actor *owner, int anim, int flag);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov135_020d15a0(void);

void func_ov135_020d116c(struct Ov134ActionNode *node)
{
    struct Ov134AreaMsg msg1;
    int results[4];
    struct Ov107SweepQuery query;
    struct Vec3 dir;
    struct Vec3 push;
    struct Vec3 at;
    struct Ov134AreaMsg msg;
    struct Ov134AreaMsg tmpl;
    FxVec vDead1;
    FxVec vDead2;
    signed char k;
    struct Ov134ActionState *state;
    FxVec *pos;
    int count;
    int i;

    state = node->pState;
    state->nElapsed30 += node->pClock->nDelta2c;
    if ((state->bFlags40 & 1) == 0 && state->nElapsed30 >= 0x999) {
        msg1 = data_ov135_020d1be2;
        pos = (FxVec *)state->pPoint38;

        vDead1.x = pos->x;
        ((u8 *)&msg1)[5] = (u8)(((unsigned int)vDead1.x.value >> 0x10 & 0x7f)
                                | ((unsigned int)vDead1.x.value >> 0x18 & 0x80));
        ((u8 *)&msg1)[6] = (u8)((unsigned int)vDead1.x.value >> 8);
        ((u8 *)&msg1)[7] = (u8)vDead1.x.value;

        vDead1.y = pos->y;
        ((u8 *)&msg1)[8] = (u8)(((unsigned int)vDead1.y.value >> 0x10 & 0x7f)
                                | ((unsigned int)vDead1.y.value >> 0x18 & 0x80));
        ((u8 *)&msg1)[9] = (u8)((unsigned int)vDead1.y.value >> 8);
        ((u8 *)&msg1)[10] = (u8)vDead1.y.value;

        vDead1.z = pos->z;
        ((u8 *)&msg1)[11] = (u8)(((unsigned int)vDead1.z.value >> 0x10 & 0x7f)
                                 | ((unsigned int)vDead1.z.value >> 0x18 & 0x80));
        ((u8 *)&msg1)[12] = (u8)((unsigned int)vDead1.z.value >> 8);
        ((u8 *)&msg1)[13] = (u8)vDead1.z.value;

        if (state->pOwner->pMsgHook24 != 0) {
            state->pOwner->pMsgHook24(state->pOwner, &msg1, 0xe);
        }
        state->bFlags40 |= 1;
    }
    if ((state->bFlags40 & 2) == 0 && state->nElapsed30 >= 0xc38) {
        state->bFlags40 |= 2;
        func_ov107_020c5af8(state->pOwner, 0x11c, 4, state->pPoint3c);
    }
    if (state->nElapsed30 >= 0xaaa) {
        k = 0;
        tmpl = data_ov135_020d1bd4;
        do {
            func_0202f384(&dir, state->pOwner->aMatrixA0, &data_02042258);
            func_01ff8d18(&dir, &dir);
            func_01ffa724(k == 0 ? 0x1000 : 0x2000, &dir, &dir);
            VEC_Add(&dir, state->pPoint3c, &query.vPos);
            query.nRadius = 0x800;
            count = func_ov107_020c8eb8(state->pOwner, &query, results);
            for (i = 0; i < count; i++) {
                if (((state->bHitMask41 >> *(u8 *)(results[i] + 0x1b4)) & 1) == 0) {
                    VEC_Subtract((void *)(results[i] + 0x74), state->pPoint3c, &push);
                    push.y = 0;
                    func_01ff8d18(&push, &push);
                    func_01ffa724(0x600, &push, &push);
                    if (func_ov107_020ca918(results[i], state->pOwner, state->pOwner, 0, &push, 0) != 0) {
                        msg = tmpl;
                        at = *(struct Vec3 *)(results[i] + 0x74);
                        at.y += 0x800;
                        vDead2.x = *(Fx32 *)&at.x;
                        ((u8 *)&msg)[5] = (u8)(((unsigned int)vDead2.x.value >> 0x10 & 0x7f)
                                                     | ((unsigned int)vDead2.x.value >> 0x18 & 0x80));
                        ((u8 *)&msg)[6] = (u8)((unsigned int)vDead2.x.value >> 8);
                        ((u8 *)&msg)[7] = (u8)vDead2.x.value;

                        vDead2.y = *(Fx32 *)&at.y;
                        ((u8 *)&msg)[8] = (u8)(((unsigned int)vDead2.y.value >> 0x10 & 0x7f)
                                                     | ((unsigned int)vDead2.y.value >> 0x18 & 0x80));
                        ((u8 *)&msg)[9] = (u8)((unsigned int)vDead2.y.value >> 8);
                        ((u8 *)&msg)[10] = (u8)vDead2.y.value;

                        vDead2.z = *(Fx32 *)&at.z;
                        ((u8 *)&msg)[11] = (u8)(((unsigned int)vDead2.z.value >> 0x10 & 0x7f)
                                                      | ((unsigned int)vDead2.z.value >> 0x18 & 0x80));
                        ((u8 *)&msg)[12] = (u8)((unsigned int)vDead2.z.value >> 8);
                        ((u8 *)&msg)[13] = (u8)vDead2.z.value;

                        if (state->pOwner->pMsgHook24 != 0) {
                            state->pOwner->pMsgHook24(state->pOwner, &msg, 0xe);
                        }
                        state->bHitMask41 |= 1 << *(u8 *)(results[i] + 0x1b4);
                        func_ov107_020c5af8(state->pOwner, 0x11c, 5, &at);
                    }
                }
            }
            k++;
        } while (k < 2);
    }
    if (*(u8 *)(state->pItem04 + 0xad) == 0) {
        func_ov107_020c9264(state->pOwner, 1, 0);
        func_0203c634(node, node->bSlot, (void *)&func_ov135_020d15a0);
    }
}
