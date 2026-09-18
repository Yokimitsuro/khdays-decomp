/* Swing tick of the ov293 enemy: the +0x14 turn step is 30 x dt / 10, the closest target
 * (cab14) goes to +4 and the +0x10 heading aims at its +0x190 from the actor's +0xb0. The
 * +0x1c velocity is the +0x39c motion's forward vector rotated into the actor frame and scaled
 * by its speed; adding it to the +0x394/+0x398 joints' +0x14 positions gives the two sweep
 * points. While the +0x40 timer stays at or below 0xc44 each point sweeps a 0x300 radius:
 * entities not yet in the +0x51 hit mask that accept a kind-0 hit pushed along the velocity get
 * the overlay's 14-byte message with the contact point through the actor's +0x24 hook, their
 * mask bit, the velocity zeroed and reaction 0x11a/5 at the point. Once the +0x4c gate byte
 * clears the turn step is zeroed, the velocity kept at +0x28 and d31b0 takes over.
 *
 * Same shape as ov122_020d12f4: Fx32-wrapped coordinates, `long` counters, two point cursors. */
typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { int x, y, z; };
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
struct Ov293AreaMsg { u16 h[7]; };
struct Ov107SweepQuery { FxVec vCentre; int nRadius; };
struct Ov293AttachBody {
    char pad000[0x14];
    struct Vec3 vPos14;
};
struct Ov107SweepEntity {
    char pad000[2];
    u16 wId2;
};
struct Ov293BoneXform { int w[11]; };
struct Ov293Actor {
    char pad000[0x24];
    void (*pMsgHook24)(struct Ov293Actor *actor, void *msg, int len);
    char pad028[0x78];
    struct Ov293BoneXform xfm;
    char pad0cc[0x394 - 0xcc];
    struct Ov293AttachBody *aBones394[2];
    void *pActionResource39c;
};
struct Ov293ActionState {
    struct Ov293Actor *pOwner;
    int pTarget04;
    char pad008[4];
    void *pEventAnchor;
    int nHeading10;
    int nTurnStep14;
    char pad018[4];
    struct Vec3 vVelocity;
    struct Vec3 vPos28;
    char pad034[0xc];
    int nElapsed40;
    char pad044[8];
    u8 *pGate4c;
    char pad050[1];
    u8 bHitMask51;
};
struct SceneFrameClock {
    char pad00[0x2c];
    int nDelta2c;
};
struct Ov293ActionNode {
    struct SceneFrameClock *pClock;
    struct Ov293ActionState *pState;
    char pad08[0x18];
    signed char bSlot;
};

extern const struct Vec3 data_02041dc8;
extern struct Ov293AreaMsg data_ov293_020d3608;
extern void func_ov293_020d31b0(void);
extern int func_ov107_020cab14(struct Ov293Actor *actor, int mode);
extern void VEC_Subtract(const void *a, const void *b, struct Vec3 *out);
extern int func_020050b4(int x, int z);
extern int func_ov107_020c9f48(void *resource, struct Vec3 *out);
extern void func_0202f384(struct Vec3 *dst, struct Ov293BoneXform *xfm, struct Vec3 *src);
extern void func_01ffa724(int scale, void *src, void *dst);
extern void VEC_Add(void *a, void *b, void *out);
extern void func_ov107_020c5af8(struct Ov293Actor *actor, int id, int mode, void *anchor);
extern int func_ov107_020c8eb8(struct Ov293Actor *actor, void *query, void *results);
extern int func_ov107_020ca918(struct Ov107SweepEntity *ent, struct Ov293Actor *a,
                               struct Ov293Actor *b, int mode, void *dir, int flag);
extern void func_0203c634(void *node, int idx, void *value);

void func_ov293_020d2e54(struct Ov293ActionNode *node)
{
    struct Ov107SweepEntity *aResults[4];
    FxVec aPoints[2];
    struct Vec3 vLocalOffset;
    struct Vec3 vToTarget;
    struct Ov107SweepQuery query;
    struct Ov293AreaMsg msg;
    struct Ov293AreaMsg tmpl;
    struct Vec3 vZero;
    FxVec vContact;
    struct Ov293ActionState *state;
    long nFound;
    long i;
    FxVec *pSweepPoint;
    FxVec *pEventPoint;
    int nPointIndex;
    int scale;

    state = node->pState;
    state->nTurnStep14 = node->pClock->nDelta2c * 30 / 10;
    state->pTarget04 = func_ov107_020cab14(state->pOwner, 0);
    if (state->pTarget04 != 0) {
        VEC_Subtract((char *)state->pTarget04 + 0x190, (char *)state->pOwner + 0xb0, &vToTarget);
        state->nHeading10 = func_020050b4(vToTarget.x, vToTarget.z);
    }
    scale = func_ov107_020c9f48(state->pOwner->pActionResource39c, &vLocalOffset);
    func_0202f384(&state->vVelocity, &state->pOwner->xfm, &vLocalOffset);
    func_01ffa724(scale, &state->vVelocity, &state->vVelocity);
    VEC_Add(&state->pOwner->aBones394[0]->vPos14, &state->vVelocity, &aPoints[0]);
    VEC_Add(&state->pOwner->aBones394[1]->vPos14, &state->vVelocity, &aPoints[1]);
    state->nElapsed40 += node->pClock->nDelta2c;
    if (state->nElapsed40 <= 0xc44) {
        pSweepPoint = aPoints;
        pEventPoint = aPoints;
        nPointIndex = 0;
        tmpl = data_ov293_020d3608;
        vZero = data_02041dc8;
        do {
            query.vCentre = *pSweepPoint;
            query.nRadius = 0x300;
            nFound = func_ov107_020c8eb8(state->pOwner, &query, aResults);
            i = 0;
            if (nFound > 0) {
                do {
                    if ((state->bHitMask51 & (1 << aResults[i]->wId2)) == 0) {
                        if (func_ov107_020ca918(aResults[i], state->pOwner, state->pOwner,
                                                0, &state->vVelocity, 0) != 0) {
                            msg = tmpl;
                            vContact.x = pSweepPoint->x;
                            ((u8 *)&msg)[7] = (u8)vContact.x.value;
                            ((u8 *)&msg)[5] = (u8)(((unsigned int)vContact.x.value >> 0x10 & 0x7f)
                                                   | ((unsigned int)vContact.x.value >> 0x18 & 0x80));
                            ((u8 *)&msg)[6] = (u8)((unsigned int)vContact.x.value >> 8);
                            vContact.y = pSweepPoint->y;
                            ((u8 *)&msg)[10] = (u8)vContact.y.value;
                            ((u8 *)&msg)[8] = (u8)(((unsigned int)vContact.y.value >> 0x10 & 0x7f)
                                                   | ((unsigned int)vContact.y.value >> 0x18 & 0x80));
                            ((u8 *)&msg)[9] = (u8)((unsigned int)vContact.y.value >> 8);
                            vContact.z = pSweepPoint->z;
                            ((u8 *)&msg)[13] = (u8)vContact.z.value;
                            ((u8 *)&msg)[11] = (u8)(((unsigned int)vContact.z.value >> 0x10 & 0x7f)
                                                    | ((unsigned int)vContact.z.value >> 0x18 & 0x80));
                            ((u8 *)&msg)[12] = (u8)((unsigned int)vContact.z.value >> 8);
                            if (state->pOwner->pMsgHook24 != 0) {
                                state->pOwner->pMsgHook24(state->pOwner, &msg, 0xe);
                            }
                            state->bHitMask51 |= 1 << aResults[i]->wId2;
                            state->vVelocity = vZero;
                            func_ov107_020c5af8(state->pOwner, 0x11a, 5, pEventPoint);
                        }
                    }
                } while (++i < nFound);
            }
            pSweepPoint++;
            pEventPoint++;
        } while (++nPointIndex < 2);
    }
    if (*state->pGate4c == 0) {
        state->nTurnStep14 = 0;
        state->vPos28 = state->vVelocity;
        func_0203c634(node, node->bSlot, func_ov293_020d31b0);
    }
}
