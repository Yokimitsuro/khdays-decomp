typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { int x, y, z; };
struct Hw60 { u16 lo : 8; u16 hi : 8; };

struct Ov120Actor {
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
    struct Ov120Actor *pOwner;
    struct Ov120Actor *pTarget;
    int aRotation8[4];
    struct Vec3 vPos18;
    char pad024[8];
    struct Vec3 vForward2c;
};

struct Ov120ActionNode {
    char pad000[4];
    struct Ov185ActionState *pState;
    char pad008[0x18];
    signed char bSlot;
};

extern struct Vec3 data_02042258;

extern struct Ov120Actor *func_ov107_020cab14(struct Ov120Actor *owner, int *pDistSq);
extern void func_0203c634(void *node, int idx, void *value);
extern int FX_Sqrt(int x);
extern void func_ov187_020d415c(struct Ov185ActionState *state, struct Vec3 *pos,
                                int nDist, int nRadius);
extern void func_0202f384(struct Vec3 *dst, void *xfm, struct Vec3 *src);
extern int func_01ff8d18(struct Vec3 *v, struct Vec3 *unit);
extern void func_01ffa724(int scale, void *src, void *dst);

/*
 * Per-frame step of the approach-target action.
 *
 * Re-acquires the lock-on target and stores it in the action state; a null
 * target ends the action.  Otherwise the squared distance the acquire call
 * returns is turned into a real distance and both body radii are subtracted,
 * leaving the gap between the two surfaces.  That gap drives the approach
 * helper, then the forward unit vector is rebuilt from the state rotation and
 * rescaled to 0x100.  Bit 1 of the actor flag byte is set while the gap is
 * within 0x1000 and cleared beyond it.  The action ends when the gap reaches
 * the actor's reach or closes to 0x800.
 *
 * The actor and node layers are the shared layouts, typed Ov120Actor and
 * Ov120ActionNode in Ghidra; only the action state is specific to this overlay.
 *
 * Two spellings of the flag edit are deliberate and not interchangeable: the
 * set arm is the explicit extract-and-reassemble, which the compiler leaves
 * untruncated, and the clear arm is the bitfield form, which carries the extra
 * halfword truncation.  The ROM has exactly that asymmetry.
 */
void func_ov187_020d4bd4(struct Ov120ActionNode *node)
{
    int nDist;
    int nTargetRadius;
    int nRange;
    struct Ov185ActionState *state;
    struct Ov120Actor *owner;
    struct Ov120Actor *target;
    struct Ov120Actor *pTail;

    state = node->pState;
    state->pTarget = func_ov107_020cab14(state->pOwner, &nDist);
    target = state->pTarget;
    if (target == 0) {
        state->pOwner->bActionState1c7 = 2;
        func_0203c634(node, node->bSlot, 0);
        return;
    }
    owner = state->pOwner;
    nRange = FX_Sqrt(nDist);
    nTargetRadius = target->nRadius80;
    nDist = nRange - (nTargetRadius + owner->nRadius80);
    func_ov187_020d415c(state, &state->vPos18, nDist, nTargetRadius);
    func_0202f384(&state->vForward2c, state->aRotation8, &data_02042258);
    func_01ff8d18(&state->vForward2c, &state->vForward2c);
    func_01ffa724(0x100, &state->vForward2c, &state->vForward2c);
    if (nDist <= 0x1000) {
        u16 v = state->pOwner->hw60;
        state->pOwner->hw60 = (u16)((v & ~0xff00)
                                    | ((((((unsigned int)v << 0x10) >> 0x18) | 2)
                                        << 0x18) >> 0x10));
    } else {
        ((struct Hw60 *)&state->pOwner->hw60)->hi &= ~2;
    }
    pTail = state->pOwner;
    if (nDist >= pTail->nReach2d8) {
        pTail->bActionState1c7 = 2;
        func_0203c634(node, node->bSlot, 0);
        return;
    }
    if (nDist > 0x800) {
        return;
    }
    pTail->bActionState1c7 = 2;
    func_0203c634(node, node->bSlot, 0);
}
