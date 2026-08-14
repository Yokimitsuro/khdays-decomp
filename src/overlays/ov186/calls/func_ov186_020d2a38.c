typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { int x, y, z; };

struct Ov120Actor {
    char pad000[0x60];
    u16 hw60;
    char pad062[0x4e];
    struct Vec3 vPosb0;
    char pad0bc[0xbe];
    u8 bLaunch17a : 1;
    char pad17b[0x15];
    struct Vec3 vPos190;
    char pad19c[0x2b];
    u8 bActionState1c7;
};

struct Ov185ActionState {
    struct Ov120Actor *pOwner;
    struct Ov120Actor *pTarget;
    char pad008[0x10];
    struct Vec3 vPos18;
    char pad024[8];
    struct Vec3 vForward2c;
    char pad038[0xc];
    struct Ov185Anim *pAnim44;
    char pad048[0x18];
    int nElapsed60;
    struct Vec3 vLaunch64;
    int nAnim70;
};

struct Ov185Anim { int nPad0; int nId4; };

struct Ov120ActionNode {
    char pad000[4];
    struct Ov185ActionState *pState;
    char pad008[0x18];
    signed char bSlot;
};

extern void func_ov186_020d2b7c(void);

extern struct Ov120Actor *func_ov107_020cab14(struct Ov120Actor *owner, int *pDistSq);
extern void func_0203c634(void *node, int idx, void *value);
extern void VEC_Subtract(struct Vec3 *a, struct Vec3 *b, struct Vec3 *out);
extern int func_01ff8d18(struct Vec3 *v, struct Vec3 *unit);
extern void func_ov186_020d1e48(struct Ov185ActionState *state, struct Vec3 *pos);
extern void func_01ffa724(int scale, void *src, void *dst);

/*
 * Per-frame step of the launch-at-target action.
 *
 * Re-acquires the lock-on target; a null target ends the action.  Otherwise it
 * takes the vector from the actor to the target and normalises it in place,
 * which also yields the distance, clamps that to 0x8000 and runs the aim
 * helper, then resets the vertical component of the advance vector to -0x200.
 *
 * The launch half only runs while bit 0 of the actor flag byte at 0x17a is set.
 * It flattens the delta on Y, normalises it and scales it by the clamped
 * distance over thirty to get the launch velocity, clears the timer, latches
 * the animation id and sets the proximity flag before handing the node to the
 * follow-up action.
 *
 * The two components of the flattened delta are read into locals before any of
 * the stores: that is what keeps both loads ahead of the write-back, which is
 * the order the ROM uses.
 */
void func_ov186_020d2a38(struct Ov120ActionNode *node)
{
    struct Vec3 vDelta;
    struct Ov185ActionState *state;
    int nLen;
    int nFlatZ;
    int nFlatX;

    state = node->pState;
    state->pTarget = func_ov107_020cab14(state->pOwner, 0);
    if (state->pTarget == 0) {
        state->pOwner->bActionState1c7 = 2;
        func_0203c634(node, node->bSlot, 0);
        return;
    }
    VEC_Subtract(&state->pTarget->vPos190, &state->pOwner->vPosb0, &vDelta);
    nLen = func_01ff8d18(&vDelta, &vDelta);
    if (nLen > 0x8000) {
        nLen = 0x8000;
    }
    func_ov186_020d1e48(state, &state->vPos18);
    state->vForward2c.y = -0x200;
    if (state->pOwner->bLaunch17a == 0) {
        return;
    }
    nFlatZ = vDelta.z;
    nFlatX = vDelta.x;
    state->vLaunch64.x = nFlatX;
    state->vLaunch64.y = 0;
    state->vLaunch64.z = nFlatZ;
    func_01ff8d18(&state->vLaunch64, &state->vLaunch64);
    func_01ffa724(nLen / 30, &state->vLaunch64, &state->vLaunch64);
    state->nElapsed60 = 0;
    state->nAnim70 = state->pAnim44->nId4;
    {
        u16 v = state->pOwner->hw60;
        state->pOwner->hw60 = (u16)((v & ~0xff00)
                                   | ((((((unsigned int)v << 0x10) >> 0x18) | 2)
                                       << 0x18) >> 0x10));
    }
    func_0203c634(node, node->bSlot, func_ov186_020d2b7c);
}
