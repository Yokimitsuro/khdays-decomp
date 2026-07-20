/* Line-of-sight test: is the path from this actor to a target point clear?
 *
 * Byte-identical triplet across ov241, ov242 and ov243 -- one enemy-AI helper
 * copied into three overlays.
 *
 * Direction is (target - origin) normalised, then rescaled to (length - margin)
 * so the probe stops short of the target by the caller margin; a non-positive
 * result is clamped to 1 rather than skipped, so a target at or inside the
 * margin still gets a minimum-length probe.
 *
 * Two casts, both against the owner world at +0x7c: first a SWEPT sphere of
 * radius 0x300, then a thin ray along the same direction. Either hit reports
 * blocked ONLY when its result record has a zero at +8, so +8 is a
 * pass-through flag rather than the hit itself -- a hit with a non-zero +8 does
 * not block. Returns 1 for clear, 0 for blocked.
 *
 * The target arrives BY VALUE in r1-r3 (a three-word VecFx32) with the margin as
 * a fifth stack word, which is why the prologue homes r0-r3.
 *
 * Declaration order is load-bearing: dir must be declared BEFORE origin. For
 * address-taken aggregates mwcc gives the FIRST declared local the HIGHEST stack
 * offset, and the ROM keeps origin low.
 */
typedef struct { int x; int y; int z; } VecFx32;

typedef struct {
    char pad00[0x7c];
    void *pWorld;            /* +0x7c */
} Owner;

typedef struct {
    char pad00[4];
    Owner *pOwner;           /* +0x04 */
    char pad08[0x6c];
    VecFx32 vOrigin;         /* +0x74 */
} Actor;

extern int VEC_Subtract(void *a, void *b, void *out);
extern int func_01ff8d18(void *in, void *out);
extern void func_01ffa724(int scale, void *in, void *out);
extern int *func_01fff8e8(void *world, VecFx32 *origin, VecFx32 *dir, int radius, void *extra);
extern int *func_01fff920(void *world, VecFx32 *origin, VecFx32 *dir);

int func_ov242_020d3dfc(Actor **ppActor, VecFx32 vTarget, int nMargin) {
    Actor *actor = *ppActor;
    Owner *owner = actor->pOwner;
    VecFx32 dir;
    VecFx32 origin;
    int len;
    int *hit;

    origin = actor->vOrigin;
    VEC_Subtract(&vTarget, &origin, &dir);
    len = func_01ff8d18(&dir, &dir) - nMargin;
    if (len <= 0) {
        len = 1;
    }
    func_01ffa724(len, &dir, &dir);
    hit = func_01fff8e8(owner->pWorld, &origin, &dir, 0x300, 0);
    if (hit != 0 && hit[2] == 0) {
        return 0;
    }
    hit = func_01fff920(owner->pWorld, &origin, &dir);
    if (hit != 0 && hit[2] == 0) {
        return 0;
    }
    return 1;
}
