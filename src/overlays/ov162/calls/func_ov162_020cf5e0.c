/* When a target is acquired and within reach, request state 4 on the owner.
 *
 * Seven-member byte-identical family: ov132, ov133, ov161, ov162, ov163, ov164,
 * ov165 -- one enemy-AI reaction copied verbatim into seven overlays, sharing
 * even its callees (all three relocs are the same symbols in every copy).
 *
 * func_ov107_020cab14 acquires the target and writes the SQUARED distance to its
 * out-parameter, so the gap is sqrt(d2) minus BOTH radii -- surface to surface,
 * not centre to centre.
 *
 * Three spellings are load-bearing, and all three came from the already-matched
 * sibling func_ov141_020cce98 rather than from experiment:
 *   - the acquired node is read BACK OUT of the field, not stored from a
 *     temporary. `field = call(); tmp = field;` keeps the call result in r0 for
 *     the store, which is the ROM shape; `tmp = call(); field = tmp;` stores the
 *     copy instead.
 *   - the two radii are summed TARGET-first. Swapping them swaps two loads.
 *   - pSelf is cached across FX_Sqrt for the radius but RE-READ afterwards for
 *     the range test; the ROM does both, so neither hand-CSE nor full reload is
 *     right on its own.
 */
typedef struct {
    char pad0000[0x80];
    int nRadius;             /* +0x080 */
    char pad0084[0x143];
    unsigned char bState;    /* +0x1c7 */
    char pad01c8[0x110];
    int nRange;              /* +0x2d8 */
} Unit;

typedef struct {
    Unit *pSelf;             /* +0x00 */
    char pad04[4];
    Unit *pTarget;           /* +0x08 */
} Owner;

typedef struct {
    char pad00[4];
    Owner *pOwner;           /* +0x04 */
    char pad08[0x18];
    signed char bTag;        /* +0x20 */
} Ctx;

extern Unit *func_ov107_020cab14(Unit *self, int *pDistSq);
extern int FX_Sqrt(int x);
extern void func_0203c634(Ctx *ctx, int tag, int c);

void func_ov162_020cf5e0(Ctx *ctx) {
    int dist;
    Owner *owner;
    Unit *self;
    Unit *target;
    owner = ctx->pOwner;

    owner->pTarget = func_ov107_020cab14(owner->pSelf, &dist);
    target = owner->pTarget;
    if (target == 0) {
        return;
    }
    self = owner->pSelf;
    dist = FX_Sqrt(dist) - (target->nRadius + self->nRadius);
    if (dist > owner->pSelf->nRange) {
        return;
    }
    owner->pSelf->bState = 4;
    func_0203c634(ctx, ctx->bTag, 0);
}
