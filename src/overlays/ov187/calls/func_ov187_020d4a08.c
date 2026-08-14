typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { int x, y, z; };
struct Hw60 { u16 lo : 8; u16 hi : 8; };

struct Ov185Actor {
    char pad000[0x60];
    u16 hw60;
    char pad062[0x1e];
    int nRadius80;
    char pad084[0x143];
    u8 bActionState1c7;
    char pad1c8[0x110];
    int nReach2d8;
};

struct Ov185ActionState {
    struct Ov185Actor *pOwner;
    struct Ov185Actor *pTarget;
    int aRotation8[4];
    struct Vec3 vPos18;
    char pad024[8];
    struct Vec3 vForward2c;
    char pad038[0x24];
    int nTurnRate5c;
    int nSpeed60;
};

struct Ov185ActionNode {
    char pad000[4];
    struct Ov185ActionState *pState;
    char pad008[0x18];
    signed char bSlot;
};

extern struct Vec3 data_02042258;
extern struct Vec3 data_02042264;

extern struct Ov185Actor *func_ov107_020cab14(struct Ov185Actor *owner, int *pDistSq);
extern int FX_Sqrt(int x);
extern void func_ov187_020d415c(struct Ov185ActionState *state, struct Vec3 *pos);
extern void func_0202f384(struct Vec3 *dst, void *xfm, struct Vec3 *src);
extern void func_01ffa724(int scale, void *src, void *dst);
extern void VEC_CrossProduct(struct Vec3 *a, struct Vec3 *b, struct Vec3 *out);
extern void VEC_Add(struct Vec3 *a, struct Vec3 *b, struct Vec3 *out);
extern int func_01ff8d18(struct Vec3 *v, struct Vec3 *unit);
extern void func_0203c634(void *node, int idx, void *value);

/*
 * Per-frame step of the circle-strafe approach.
 *
 * Re-acquires the target and turns the squared distance into the gap between
 * the two body surfaces, setting the proximity bit of the actor flag byte while
 * that gap is within 0x1000 and clearing it beyond.  Past the actor's reach it
 * does nothing more.  Otherwise it runs the aim helper and rebuilds the forward
 * vector, then picks one of three behaviours by gap: inside 0x800 it advances
 * straight ahead at half speed; between 0x800 and 0x1000 it crosses the forward
 * vector with the world up axis and adds the result back, which swings the
 * movement sideways into a circling arc scaled by speed times turn rate; past
 * 0x1000 it ends the action.
 *
 * Three shapes here are deliberate.  The halfword load feeding the proximity
 * flag sits inside the taken arm, which is what keeps the pair of arms as a
 * branch instead of predicated code.  The two stack vectors are declared with
 * the forward vector first so they land at the offsets the ROM uses.  And the
 * last test is written the way round that leaves the arc as the fall-through
 * and the end-of-action as the branch target.
 */
void func_ov187_020d4a08(struct Ov185ActionNode *node)
{
    int nDist;
    struct Vec3 vForward;
    struct Vec3 vCross;
    struct Ov185ActionState *state;
    struct Ov185Actor *owner;
    struct Ov185Actor *target;
    u16 v;

    state = node->pState;
    state->pTarget = func_ov107_020cab14(state->pOwner, &nDist);
    target = state->pTarget;
    if (target == 0) {
        return;
    }
    owner = state->pOwner;
    nDist = FX_Sqrt(nDist) - (target->nRadius80 + owner->nRadius80);
    if (nDist <= 0x1000) {
        v = state->pOwner->hw60;
        state->pOwner->hw60 = (u16)((v & ~0xff00)
                                    | ((((((unsigned int)v << 0x10) >> 0x18) | 2)
                                        << 0x18) >> 0x10));
    } else {
        ((struct Hw60 *)&state->pOwner->hw60)->hi &= ~2;
    }
    if (nDist > state->pOwner->nReach2d8) {
        return;
    }
    func_ov187_020d415c(state, &state->vPos18);
    func_0202f384(&vForward, state->aRotation8, &data_02042258);
    if (nDist <= 0x800) {
        func_01ffa724(state->nSpeed60 / 2, &vForward, &state->vForward2c);
        return;
    }
    if (nDist <= 0x1000) {
        VEC_CrossProduct(&vForward, &data_02042264, &vCross);
        VEC_Add(&vCross, &vForward, &state->vForward2c);
        func_01ff8d18(&state->vForward2c, &state->vForward2c);
        func_01ffa724(state->nSpeed60 * state->nTurnRate5c, &state->vForward2c,
                      &state->vForward2c);
        return;
    }
    state->pOwner->bActionState1c7 = 4;
    func_0203c634(node, node->bSlot, 0);
}
