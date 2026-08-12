/*
 * func_ov122_020d01a8 -- Ov122_Actor_OnHit.
 *
 * The actor's hit handler, installed by the ov122 initializer. Shared byte-for-byte with
 * ov120 and ov121; against both of them even the relocations match.
 *
 * A hit is refused outright once the stagger timer has run out. Otherwise the caller's
 * parameter and the event's contact point are stashed in the action state, and while the actor
 * is in action state 7 a hit carrying both flag 1 and flag 0x10 promotes it to state 8 and stops
 * there. States 6 and 7 publish 0 and 1 back into the event's mode field.
 *
 * The ov107 charge then decides the damage, which is reported back in the event and drained from
 * the stagger timer, clamped to the actor's cap and floored at zero; emptying it puts the actor
 * in state 3, and flag 0x8000 puts it in state 5. Flag 0x4000 short-cuts all of that: it writes 1
 * into the low half of the event's result word and goes straight to state 5.
 *
 * Finally a hit that actually charged flips the state's facing bit and fires reaction 0x11a,
 * choosing modes 2/3 when flag 0x22 is present and 0/1 otherwise, except for kind-0x80 hits that
 * carry both flag 8 and flag 0x80.
 *
 * Ghidra: Ov122_Actor_OnHit(Ov120Actor *pActor, int nParam, ActorHitEvent *pHit), types
 * /khdays/Ov120Actor, /khdays/Ov120ActionState, /khdays/ActorHitEvent and /khdays/Vec3.
 *
 * Byte-exact codegen notes (mwccarm 3.0/139):
 *  - The contact point moves as ONE three-word struct copy; the ROM emits ldm/stm for it. Three
 *    scalar assignments cost six extra instructions.
 *  - The drain re-reads the damage out of the event instead of using the value the charge call
 *    returned. Using the returned local drops both the second materialisation of the halfword
 *    base and the reload, and the function comes out eight bytes short.
 *  - The 6/7 publish is a switch, not an if/else-if chain: the switch puts the state-6 body out
 *    of line the way the ROM lays it out, while the chain predicates it inline and saves an
 *    instruction. An explicit goto and an inverted if produce the same bytes; the switch is
 *    simply the readable one.
 *  - The flag word and the result word are 16-bit bitfield pairs, the idiom the ov294 hit
 *    handler records; reading them as a plain word with masks changes the shifts. The same
 *    goes for the state's facing bit, which is a one-bit field, not a byte masked by hand.
 */
typedef unsigned char u8;

struct Vec3 {
    int x;
    int y;
    int z;
};

struct Ov120Actor;

struct Ov120ActionState {
    struct Ov120Actor *pOwner;
    char pad004[4];
    void *pTarget;
    void *pEventAnchor;
    char pad010[0x24];
    struct Vec3 vHitPoint;
    char pad040[4];
    int nHitParam44;
    char pad048[6];
    u8 bFacing : 1;
};

struct Ov120Actor {
    char pad000[0x1c6];
    char actionState;
    u8 bActionState1c7;
    char pad1c8[0x4c];
    struct Ov120ActionState *pActionState214;
    short nStaggerCap218;
    short nStaggerTimer21a;
};

struct ActorHitEvent {
    unsigned int uFlagsLo : 16;
    unsigned int uFlagsHi : 16;
    struct Vec3 vPoint;
    char pad010[0x10];
    unsigned int uMode20;
    unsigned int uResultLo : 16;
    unsigned int uResultHi : 16;
    int nDamage;
};

extern int func_ov107_020c89e8(struct Ov120Actor *actor, struct ActorHitEvent *hit);
extern void func_ov107_020c5af8(struct Ov120Actor *actor, int id, unsigned short mode,
                                void *anchor);

int func_ov122_020d01a8(struct Ov120Actor *actor, int nParam, struct ActorHitEvent *hit)
{
    struct Ov120ActionState *state = actor->pActionState214;
    int taken;
    int delta;
    int rem;
    char actionState;

    if (actor->nStaggerTimer21a <= 0) {
        return 0;
    }
    state->nHitParam44 = nParam;
    state->vHitPoint = hit->vPoint;
    actionState = state->pOwner->actionState;
    if (actionState == 7 && (hit->uFlagsLo & 1) != 0 && (hit->uFlagsLo & 0x10) != 0) {
        state->pOwner->bActionState1c7 = 8;
        return 1;
    }
    switch (actionState) {
    case 6:
        hit->uMode20 = 0;
        break;
    case 7:
        hit->uMode20 = 1;
        break;
    }
    taken = func_ov107_020c89e8(actor, hit);
    hit->nDamage = taken;
    if ((hit->uFlagsLo & 0x4000) != 0) {
        hit->uResultLo = 1;
        state->pOwner->bActionState1c7 = 5;
        return 1;
    }
    delta = actor->nStaggerTimer21a - hit->nDamage;
    if (delta < 0) {
        rem = 0;
    } else {
        rem = actor->nStaggerCap218;
        if (delta <= rem) {
            rem = delta;
        }
    }
    actor->nStaggerTimer21a = (short)rem;
    if (actor->nStaggerTimer21a == 0) {
        state->pOwner->bActionState1c7 = 3;
    } else if ((hit->uFlagsLo & 0x8000) != 0) {
        state->pOwner->bActionState1c7 = 5;
    }
    if (hit->nDamage > 0) {
        if ((hit->uFlagsLo & 8) == 0 || (hit->uFlagsLo & 0x80) == 0
            || hit->uFlagsHi != 0x80) {
            if ((hit->uFlagsLo & 0x22) != 0) {
                state->bFacing = state->bFacing + 1;
                func_ov107_020c5af8(actor, 0x11a, (state->bFacing & 1) ? 2 : 3,
                                    state->pEventAnchor);
            } else {
                state->bFacing = state->bFacing + 1;
                func_ov107_020c5af8(actor, 0x11a, (state->bFacing & 1) ? 0 : 1,
                                    state->pEventAnchor);
            }
        }
    }
    return 1;
}
