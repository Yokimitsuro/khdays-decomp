/* func_ov165_020d22ec: hit handler of the ov163 enemy (x3), ported from the matched ov131 sibling; the health always drops here, and a kind-4 hit in sub-state 7 flattens and normalises the impact direction (falling back to the anchor-to-source direction when it is vertical). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

struct HitState {
    char *pTarget;
    char pad04[0x20];
    VecFx32 vPoint;
    char pad30[0x18];
    int nSource48;
    char pad4c[4];
    VecFx32 *pAnchor50;
    int nParam54;
    char pad58[0x10];
    int nFlag68;
    char pad6c[1];
    u8 bAlternate6d : 1;
};

struct HitMsg {
    u32 uFlags : 16;
    u32 uKind : 16;
    VecFx32 vPoint;
    char pad10[0x10];
    u32 uMode20;
    u32 uResult24;
    int nDamage28;
};

extern int func_ov107_020c89e8(char *actor, struct HitMsg *msg);
extern void func_ov107_020c5af8(char *actor, int id, u16 mode, int param);
extern int func_01ff8d18(VecFx32 *v, VecFx32 *out);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);

int func_ov165_020d22ec(char *actor, int source, struct HitMsg *msg)
{
    struct HitState *hs;
    int state;
    int left;
    int step;
    VecFx32 flat;
    VecFx32 away;

    hs = *(struct HitState **)(actor + 0x214);
    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }

    state = *(signed char *)(hs->pTarget + 0x1c6);
    if (state != 6) {
        if (state == 8) {
            msg->uMode20 = 1;
        }
    } else {
        msg->uMode20 = 2;
    }

    msg->nDamage28 = func_ov107_020c89e8(actor, msg);

    if ((msg->uFlags & 0x4000) != 0) {
        hs->vPoint = msg->vPoint;
        msg->uResult24 = msg->uResult24 & 0xffff0000 | 1;
        *(signed char *)(hs->pTarget + 0x1c7) = 5;
        return 1;
    }

    left = *(short *)(actor + 0x21a) - msg->nDamage28;
    if (left < 0) {
        step = 0;
    } else {
        step = *(short *)(actor + 0x218);
        if (left <= step) {
            step = left;
        }
    }
    *(short *)(actor + 0x21a) = (short)step;

    hs->nSource48 = source;
    hs->vPoint = msg->vPoint;

    if (*(short *)(actor + 0x21a) == 0) {
        *(signed char *)(hs->pTarget + 0x1c7) = 3;
    } else {
        if ((msg->uKind & 0x80) != 0) {
            *(signed char *)(hs->pTarget + 0x1c7) = 8;
        } else {
            if ((msg->uFlags & 1) != 0 && (msg->uFlags & 0x10) != 0 &&
                *(signed char *)(hs->pTarget + 0x1c6) == 6) {
                *(signed char *)(hs->pTarget + 0x1c7) = 7;
            } else if (*(signed char *)(hs->pTarget + 0x1c6) == 7) {
                if ((msg->uFlags & 4) != 0) {
                    hs->vPoint.x = msg->vPoint.x;
                    hs->vPoint.y = 0;
                    hs->vPoint.z = msg->vPoint.z;
                    hs->nFlag68 = 1;
                    func_01ff8d18(&hs->vPoint, &hs->vPoint);
                    flat = hs->vPoint;
                    flat.y = 0;
                    if (func_01ff8d18(&flat, &flat) == 0) {
                        VEC_Subtract(hs->pAnchor50, (VecFx32 *)(source + 0x190), &away);
                        away.y = 0;
                        func_01ff8d18(&away, &hs->vPoint);
                    }
                }
            } else if ((msg->uFlags & 0x8000) != 0) {
                *(signed char *)(hs->pTarget + 0x1c7) = 5;
            }
        }
    }

    if (msg->nDamage28 > 0) {
        if ((msg->uFlags & 8) == 0 || (msg->uFlags & 0x80) == 0 ||
            msg->uKind != 0x80) {
            if ((msg->uFlags & 0x22) != 0) {
                hs->bAlternate6d = hs->bAlternate6d + 1;
                func_ov107_020c5af8(actor, 0x153,
                                    (u16)((hs->bAlternate6d & 1) != 0 ? 2 : 3), hs->nParam54);
            } else {
                hs->bAlternate6d = hs->bAlternate6d + 1;
                func_ov107_020c5af8(actor, 0x153,
                                    (u16)((hs->bAlternate6d & 1) != 0 ? 0 : 1), hs->nParam54);
            }
        }
    }
    return 1;
}
