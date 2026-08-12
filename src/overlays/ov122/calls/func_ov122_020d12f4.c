typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { int x, y, z; };
struct Word { int w; };
struct Ov120AreaMsg { u16 h[7]; };
struct Ov107SweepQuery { struct Vec3 vCentre; int nRadius; };

struct Ov120AttachBody {
    char pad000[0x14];
    struct Vec3 vPos14;
};

struct Ov107SweepEntity {
    char pad000[2];
    u16 wId2;
};

struct Ov120BoneXform { int w[11]; };

struct Ov120Actor {
    char pad000[0x24];
    void (*pMsgHook24)(struct Ov120Actor *actor, void *msg, int len);
    char pad028[0x78];
    struct Ov120BoneXform xfm;
    char pad0cc[0x2c4];
    struct Ov120AttachBody *aBones390[4];
    void *pActionResource3a0;
};

struct Ov120ActionState {
    struct Ov120Actor *pOwner;
    char pad004[8];
    void *pEventAnchor;
    char pad010[0xc];
    struct Vec3 vVelocity;
    struct Vec3 vPos28;
    char pad034[0xc];
    int nElapsed40;
    char pad044[4];
    u8 *pGate48;
    u8 bOneShot4c;
    u8 bHitMask4d;
};

struct SceneFrameClock {
    char pad00[0x2c];
    int nDelta2c;
};

struct Ov120ActionNode {
    struct SceneFrameClock *pClock;
    struct Ov120ActionState *pState;
    char pad08[0x18];
    signed char bSlot;
};

extern const struct Vec3 data_02041dc8;
extern struct Ov120AreaMsg data_ov122_020d1b42;
extern void func_ov122_020d1638(void);

extern int func_ov107_020c9f48(void *resource, struct Vec3 *out);
extern void func_0202f384(struct Vec3 *dst, struct Ov120BoneXform *xfm, struct Vec3 *src);
extern void func_01ffa724(int scale, void *src, void *dst);
extern void VEC_Add(void *a, void *b, void *out);
extern void func_ov107_020c0b90(struct Ov120Actor *actor, int mode, struct Vec3 v,
                                int flag);
extern void func_ov107_020c5af8(struct Ov120Actor *actor, int id, int mode, void *anchor);
extern int func_ov107_020c8eb8(struct Ov120Actor *actor, void *query, void *results);
extern int func_ov107_020ca918(struct Ov107SweepEntity *ent, struct Ov120Actor *a,
                               struct Ov120Actor *b, int mode, void *dir, int flag);
extern void func_0203c634(void *node, int idx, void *value);

/*
 * Per-frame step of the two-point sweep attack action.
 *
 * Builds the swing offset from the action resource, rotates it into the actor
 * frame and scales it, then offsets bone attachments 1 and 2 by it to get the
 * two sweep points.  At 0x2a8 ticks it fires the one-shot effect and event.
 * From 0xff0 ticks it sweeps a 0x300 radius around each point, skips entities
 * already recorded in the per-action hit mask, packs the contact point into the
 * 14-byte area message and publishes it through the actor message hook.  Once
 * the gate byte clears it publishes the offset and advances the node to the
 * follow-up action.
 *
 * The two point cursors hold the same address throughout: the ROM keeps one for
 * the sweep query and the packed contact point and a second for the event
 * anchor.  Both counters are declared long and in this order on purpose -- long
 * and int are both 32 bits here, so the code shape is unchanged, but the
 * allocation order is what places the loop counter and the two cursors in the
 * registers the ROM uses.
 */
void func_ov122_020d12f4(struct Ov120ActionNode *node)
{
    struct Ov107SweepEntity *aResults[4];
    struct Vec3 aPoints[2];
    struct Vec3 vLocalOffset;
    struct Ov107SweepQuery query;
    struct Ov120AreaMsg msg;
    struct Ov120AreaMsg tmpl;
    struct Vec3 vZero;
    struct Vec3 vContact;
    struct Ov120ActionState *state;
    long nFound;
    long i;
    struct Vec3 *pSweepPoint;
    struct Vec3 *pEventPoint;
    int nPointIndex;
    int scale;

    state = node->pState;
    scale = func_ov107_020c9f48(state->pOwner->pActionResource3a0, &vLocalOffset);
    func_0202f384(&state->vVelocity, &state->pOwner->xfm, &vLocalOffset);
    func_01ffa724(scale, &state->vVelocity, &state->vVelocity);
    VEC_Add(&state->pOwner->aBones390[1]->vPos14, &state->vVelocity, &aPoints[0]);
    VEC_Add(&state->pOwner->aBones390[2]->vPos14, &state->vVelocity, &aPoints[1]);
    state->nElapsed40 += node->pClock->nDelta2c;
    if (state->bOneShot4c == 0 && state->nElapsed40 >= 0x2a8) {
        state->bOneShot4c = 1;
        func_ov107_020c0b90(state->pOwner, 2, data_02041dc8, 0);
        func_ov107_020c5af8(state->pOwner, 0x11a, 4, state->pEventAnchor);
    }
    if (state->nElapsed40 >= 0xff0) {
        pSweepPoint = aPoints;
        pEventPoint = aPoints;
        nPointIndex = 0;
        tmpl = data_ov122_020d1b42;
        vZero = data_02041dc8;
        do {
            query.vCentre = *pSweepPoint;
            query.nRadius = 0x300;
            nFound = func_ov107_020c8eb8(state->pOwner, &query, aResults);
            i = 0;
            if (nFound > 0) {
                do {
                    if ((state->bHitMask4d & (1 << aResults[i]->wId2)) == 0) {
                        if (func_ov107_020ca918(aResults[i], state->pOwner, state->pOwner,
                                                1, &state->vVelocity, 0) != 0) {
                            msg = tmpl;

                            *(struct Word *)&vContact.x = *(struct Word *)&pSweepPoint->x;
                            ((u8 *)&msg)[7] = (u8)vContact.x;
                            ((u8 *)&msg)[5] = (u8)(((unsigned int)vContact.x >> 0x10 & 0x7f)
                                                   | ((unsigned int)vContact.x >> 0x18 & 0x80));
                            ((u8 *)&msg)[6] = (u8)((unsigned int)vContact.x >> 8);

                            *(struct Word *)&vContact.y = *(struct Word *)&pSweepPoint->y;
                            ((u8 *)&msg)[10] = (u8)vContact.y;
                            ((u8 *)&msg)[8] = (u8)(((unsigned int)vContact.y >> 0x10 & 0x7f)
                                                   | ((unsigned int)vContact.y >> 0x18 & 0x80));
                            ((u8 *)&msg)[9] = (u8)((unsigned int)vContact.y >> 8);

                            *(struct Word *)&vContact.z = *(struct Word *)&pSweepPoint->z;
                            ((u8 *)&msg)[13] = (u8)vContact.z;
                            ((u8 *)&msg)[11] = (u8)(((unsigned int)vContact.z >> 0x10 & 0x7f)
                                                    | ((unsigned int)vContact.z >> 0x18 & 0x80));
                            ((u8 *)&msg)[12] = (u8)((unsigned int)vContact.z >> 8);

                            if (state->pOwner->pMsgHook24 != 0) {
                                state->pOwner->pMsgHook24(state->pOwner, &msg, 0xe);
                            }
                            state->bHitMask4d |= 1 << aResults[i]->wId2;
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
    if (*state->pGate48 == 0) {
        state->vPos28 = state->vVelocity;
        func_0203c634(node, node->bSlot, func_ov122_020d1638);
    }
}
