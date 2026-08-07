typedef unsigned char u8;

/* The hit state hanging off the actor; only its owner pointer is used here. */
struct HitState {
    char *pOwner;
};

struct HitMsg {
    char pad00[0x28];
    int nDamage28;
};

extern int func_ov107_020c89e8(char *actor, struct HitMsg *msg);

/* Registered hit handler: applies the damage the shared helper computes,
   clamps the remaining hit points into [0, cap], and requests state 3 once
   they run out. The middle argument is part of the handler signature and is
   not read here. */
int func_ov285_020d1c48(char *actor, int source, struct HitMsg *msg)
{
    struct HitState *hs;
    int left;
    int next;

    hs = *(struct HitState **)(actor + 0x214);
    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }
    left = func_ov107_020c89e8(actor, msg);
    msg->nDamage28 = left;
    left = *(short *)(actor + 0x21a) - left;
    if (left < 0) {
        next = 0;
    } else {
        next = *(short *)(actor + 0x218);
        if (left <= *(short *)(actor + 0x218)) {
            next = left;
        }
    }
    *(short *)(actor + 0x21a) = (short)next;
    if (*(short *)(actor + 0x21a) == 0) {
        *(u8 *)(hs->pOwner + 0x1c7) = 3;
    }
    return 1;
}
