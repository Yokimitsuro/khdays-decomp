/*
 * func_ov289_020d5d64 -- Ov287_Actor_ResolveHit.
 *
 * Hit resolution handler installed in the +0x1d0 slot by func_ov289_020d5664, shared with
 * ov288 and ov289. While the owner is in state 2 it either latches the other object and moves
 * the owner to state 4, when the event source's high halfword is 0x6b, or cancels through
 * ov107::020c9264. If the request asks for a latch and nothing is latched yet it stores the
 * other object, copies the contact point into the state block, answers 6 and turns that point
 * into a direction from the owner with the vertical component cleared; otherwise it answers 4.
 * It then runs the damage call and, unless the request is the guard-break shape, starts impact
 * event 0x15b with one of two sub-ids chosen by a toggle it flips afterwards. Always returns 1.
 *
 * Ghidra: Ov287_Actor_ResolveHit(Ov287Actor *pActor, void *pOther, ActorHitEvent *pEvent),
 * types /khdays/ActorHitState, /khdays/ActorHitEvent and /khdays/ImpactIdPairs, with
 * pHitState214 carved out of /khdays/Actor's former padding.
 *
 * Byte-exact codegen notes (mwccarm 3.0/139):
 *  - The request word is a pair of 16-bit BITFIELDS, not a u32 read through casts. Both
 *    spellings emit the same ldr plus lsl/lsr, but the cast form allocates three registers
 *    where the original uses two: it keeps the raw word in one register, narrows through a
 *    second and lands the halfword in a third. The bitfield pair narrows in place and matches.
 *    That single change was worth seven instructions here and no other spelling reached it --
 *    locals, masks, condition shape, declaration order and callee return types were all
 *    measured neutral.
 *  - The id table is copied as two two-byte members, the second one first, which is the order
 *    the original loads and stores them in. A single four-byte copy comes out ascending.
 *  - The two indexed reads use separate members so the base address is formed with
 *    `add r0, sp, #0` and `add r0, sp, #2`; indexing one array with `i` and `i + 2` makes mwcc
 *    add to the index instead.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

struct ImpactIdPair {
    u8 v[2];
};

struct ImpactIdPairs {
    struct ImpactIdPair normal;
    struct ImpactIdPair alternate;
};

struct HitState {
    void *pOwner;
    char pad004[4];
    void *pTarget;
    void *pEventAnchor;
    char pad010[0x18];
    VecFx32 vToTarget;
    char pad034[0x21];
    u8 impactToggle;
};

struct Actor {
    char pad000[0x214];
    struct HitState *pHitState214;
};

struct HitEvent {
    unsigned request : 16;
    unsigned kind : 16;
    VecFx32 vPoint;
    char pad010[4];
    int source14;
    char pad018[0xc];
    u32 result24;
    int damage28;
};

extern void func_ov107_020c9264(void *owner, int state, int arg);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *ab);
extern int func_ov107_020c89e8(struct Actor *actor, struct HitEvent *event);
extern void func_ov107_020c5af8(struct Actor *actor, int id, int sub, void *anchor);

extern const struct ImpactIdPairs data_ov289_020d7134;

int func_ov289_020d5d64(struct Actor *actor, void *other, struct HitEvent *event)
{
    struct ImpactIdPairs ids;
    struct HitState *st;

    st = actor->pHitState214;
    ids.alternate = data_ov289_020d7134.alternate;
    ids.normal = data_ov289_020d7134.normal;
    if (*(signed char *)((char *)st->pOwner + 0x1c6) == 2) {
        if ((event->source14 >> 16) == 0x6b) {
            st->pTarget = other;
            *(u8 *)((char *)st->pOwner + 0x1c7) = 4;
        } else {
            func_ov107_020c9264(st->pOwner, 2, 0);
        }
    }
    if ((event->request & 0x20) != 0 && st->pTarget == 0) {
        st->pTarget = other;
        st->vToTarget = event->vPoint;
        event->result24 = event->result24 & 0xffff0000 | 6;
        if (st->pTarget != 0) {
            VEC_Subtract((VecFx32 *)((char *)st->pOwner + 0xb0),
                         (VecFx32 *)((char *)st->pTarget + 0x190), &st->vToTarget);
            st->vToTarget.y = 0;
        }
    } else {
        event->result24 = event->result24 & 0xffff0000 | 4;
    }
    event->damage28 = func_ov107_020c89e8(actor, event);
    if (event->damage28 > 0) {
        if ((event->request & 8) == 0 || (event->request & 0x80) == 0 || event->kind != 0x80) {
            if (event->request & 0x22) {
                func_ov107_020c5af8(actor, 0x15b, ids.normal.v[st->impactToggle],
                                    st->pEventAnchor);
            } else {
                func_ov107_020c5af8(actor, 0x15b, ids.alternate.v[st->impactToggle],
                                    st->pEventAnchor);
            }
            st->impactToggle = st->impactToggle ^ 1;
        }
    }
    return 1;
}
