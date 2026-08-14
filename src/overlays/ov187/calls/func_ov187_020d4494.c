typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 { int x, y, z; };
struct Quat { int x, y, z, w; };
struct Hw60 { u16 lo : 8; u16 hi : 8; };

struct TargetFlags40 {
    int b0 : 1;
    int bSolid : 1;
    int rest : 30;
};

struct Ov185Target {
    char pad000[0x40];
    struct TargetFlags40 flags40;
    char pad044[0x1c];
    u16 hw60;
    char pad062[0x12];
    struct Vec3 vPos74;
    int nRadius80;
};

struct ListNode {
    struct Ov185Target *pItem;
};

struct Ov185Scene {
    char pad000[0xa8];
    char listA8[0x10];
};

struct Ov185Actor {
    char pad000[0x04];
    struct Ov185Scene *pScene04;
    char pad008[0x6c];
    struct Vec3 vPos74;
    int nRadius80;
    char pad084[0x1c];
    struct Quat qSrtA0;
    char pad0b0[0x40];
    struct Vec3 vDeltaF0;
    char pad0fc[0xca];
    signed char bAction1c6;
};

struct Ov185ActionState {
    struct Ov185Actor *pOwner;
    char pad004[0x04];
    struct Quat qRot08;
    struct Quat qTarget18;
    int nBlend28;
    struct Vec3 vForward2c;
    char pad038[0x04];
    int nTimer3c;
    int nAngle40;
    char pad044[0x20];
    int nCooldown64;
    char pad068[0x05];
    u8 bEffect6d;
};

struct Ov185Frame {
    char pad000[0x2c];
    int nDelta2c;
};

struct Ov185ActionNode {
    struct Ov185Frame *pFrame;
    struct Ov185ActionState *pState;
};

extern const short data_0203d210[];
extern const struct Vec3 data_02041dc8;

extern void func_0202f55c(struct Quat *out, int t, struct Quat *a, struct Quat *b);
extern void func_0203c9d0(struct Quat *dst, struct Quat *src);
extern struct ListNode *func_01fffd70(void *list);
extern struct ListNode *func_01fffd8c(void *list);
extern void VEC_Subtract(const struct Vec3 *a, const struct Vec3 *b, struct Vec3 *out);
extern int func_01ff8d18(struct Vec3 *v, struct Vec3 *unit);
extern int func_ov107_020ca918(struct Ov185Target *candidate, struct Ov185Actor *owner,
                               struct Ov185Actor *source, int mode,
                               const struct Vec3 *v, int flags);
extern void func_ov107_020c0b90(struct Ov185Actor *owner, int mode, struct Vec3 v,
                                int flag);

/*
 * Per-frame step of the sweep attack.
 *
 * Every frame it blends the stored rotation towards its target and publishes the
 * result to the actor.  While the actor is in action 2 or 4 it advances a
 * fixed-point angle by the frame delta and adds a twentieth of that angle's sine
 * to the vertical speed, which is the hover.  Every 0x800 of accumulated time it
 * walks the scene list once: any solid, enabled entity whose distance minus the
 * two radii is within 0xc00 takes a hit, and the contact effect starts on the
 * first hit of the sweep.  A sweep that finds nothing, or the actor moving on to
 * action 5, stops the effect again.  Whatever the action, a positive cooldown
 * counts down, the accumulated velocity is published to the actor, and the
 * accumulator is cleared.
 *
 * The angle-to-table-index step is the shared 48-bit multiply by one over two
 * pi, the same one the bone spin action uses.
 *
 * Two things pin the register assignment, and both are the shape of a live
 * range rather than anything visible in the output.  The owner is cached for the
 * action test but the tail of the else-if reaches through the state again, which
 * ends the cached copy's live range at the test; written the other way the
 * compiler keeps it alive to the end and the three registers that carry the hit
 * flag, the sweep's own owner and the scene rotate by one.  The declaration
 * order then settles which of those three gets which register.
 */
void func_ov187_020d4494(struct Ov185ActionNode *node)
{
    int nAngle;
    int nIndex;
    int nDist;
    struct Ov185Actor *owner;
    struct Ov185ActionState *state;
    int bHit;
    struct Ov185Scene *scene;
    struct Ov185Target *target;
    struct Vec3 vDelta;
    struct ListNode *pNode;

    state = node->pState;
    func_0202f55c(&state->qRot08, state->nBlend28, &state->qRot08, &state->qTarget18);
    func_0203c9d0(&state->pOwner->qSrtA0, &state->qRot08);
    owner = state->pOwner;
    if (owner->bAction1c6 == 2 || owner->bAction1c6 == 4) {
        bHit = 0;
        nAngle = state->nAngle40 + node->pFrame->nDelta2c;
        state->nAngle40 = nAngle;
        nIndex = (u16)((nAngle * 4 * 0x28BE60DB9391LL + 0x80000000000LL) >> 44) >> 4;
        state->vForward2c.y += data_0203d210[nIndex * 2] / 20;

        state->nTimer3c = state->nTimer3c + node->pFrame->nDelta2c;
        if (state->nTimer3c >= 0x800) {
            owner = state->pOwner;
            scene = owner->pScene04;
            state->nTimer3c = 0;
            pNode = func_01fffd70(scene->listA8);
            target = pNode == 0 ? 0 : pNode->pItem;
            while (target != 0) {
                if (target->flags40.bSolid
                    && (((struct Hw60 *)&target->hw60)->lo & 1) != 0) {
                    VEC_Subtract(&target->vPos74, &owner->vPos74, &vDelta);
                    nDist = func_01ff8d18(&vDelta, &vDelta);
                    if (nDist - (owner->nRadius80 + target->nRadius80) <= 0xc00) {
                        func_ov107_020ca918(target, state->pOwner, state->pOwner, 0,
                                            &data_02041dc8, 0x10);
                        bHit = 1;
                        if (state->bEffect6d == 0) {
                            func_ov107_020c0b90(state->pOwner, 0, data_02041dc8, 0);
                            state->bEffect6d = 1;
                        }
                    }
                }
                pNode = func_01fffd8c(scene->listA8);
                target = pNode == 0 ? 0 : pNode->pItem;
            }
            if (bHit == 0 && state->bEffect6d != 0) {
                func_ov107_020c0b90(state->pOwner, 1, data_02041dc8, 0);
                state->bEffect6d = 0;
            }
        }
    } else if (owner->bAction1c6 == 5 && state->bEffect6d != 0) {
        func_ov107_020c0b90(state->pOwner, 1, data_02041dc8, 0);
        state->bEffect6d = 0;
    }
    if (state->nCooldown64 > 0) {
        state->nCooldown64 -= node->pFrame->nDelta2c;
    }
    state->pOwner->vDeltaF0 = state->vForward2c;
    state->vForward2c = data_02041dc8;
}
