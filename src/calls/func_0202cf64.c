/* func_0202cf64 -- resolve the floor under a mover, MAIN. Returns 0 for an inactive mover (+0x46 < 0).
 * Five downward rays (0x50000 long) are cast from above the owner's position (lifted by 0xb33, or by
 * the mover height +0x19a when that is taller) around a ring of the owner's radius (0x900, or the
 * owner's +0x148 - 10 past 0xd00) starting in its facing direction and turning 90 degrees after each
 * ray that lands below the head. The highest hit within 0x1ccd of the best one is kept (with its hit
 * record); the first ray's floor normal flags a steep slope (y < 0xf33), which freezes the choice. A
 * mover standing on a single hit of a ledge while walking is pushed off it (+0x400 along the walk).
 * When any ray landed, a straight ray from the chosen origin settles the floor: a floor object within
 * 0x400 of the feet marks moving platforms (their riders get flag 0x1000 and the floor point) and a
 * sliding floor (func_020293a8) starts a slide along the floor normal (or backwards when flat).
 * Otherwise the floor hit is recorded (+0x48, +0xe0, +0xec = 2) and, when the fall `*fall` reaches it
 * (or a snap-to-floor fall is close enough), the mover lands: y is set, the vertical speed becomes
 * 0x80000000, flag 4 set and the slide cleared. Returns 1 on landing.
 * Load-bearing spellings: the ray direction goes through the SDK's VEC_Set inline (its zero is the
 * register the ROM subtracts 0x50000 from), `count = 0` follows it, `i` is declared before `count`,
 * the ring offset multiplies through an inline (sin * radius operand order) and the height copy of
 * the second cast is an int (an s16 delays the fall load past the spill stores). */
typedef short s16;
typedef unsigned short u16;
typedef int fx32;
typedef long long s64;

typedef struct { fx32 x, y, z; } VecFx32;

typedef struct CollCastParams {
    VecFx32 *origin;                    /* +0x00 */
    VecFx32 *direction;                 /* +0x04 */
    fx32 radius;                        /* +0x08 */
    u16 directionIsUnit;                /* +0x0c */
    u16 flags;                          /* +0x0e */
    void *exclude;                      /* +0x10 */
} CollCastParams;

typedef struct FloorNode {
    char pad000[0x158];
    int moving;                         /* +0x158 */
} FloorNode;

typedef struct FloorObject {
    char pad00[0x28];
    FloorNode *node;                    /* +0x28 */
} FloorObject;

typedef struct HitRecord {
    void *model;                        /* +0x00 */
    char *face;                         /* +0x04 */
    FloorObject *obj;                   /* +0x08 */
    fx32 distance;                      /* +0x0c */
    int rest[34];
} HitRecord;

typedef struct Rider {
    char pad000[0x20];
    FloorNode *node;                    /* +0x020 */
    int flags;                          /* +0x024 */
    char pad028[0x3a0 - 0x28];
    VecFx32 floorPt;                    /* +0x3a0 */
} Rider;

typedef struct MoverOwner {
    char pad000[0x80];
    u16 angle;                          /* +0x080 */
    char pad082[0x148 - 0x82];
    fx32 radius;                        /* +0x148 */
} MoverOwner;

typedef struct Mover {
    MoverOwner *owner;                  /* +0x000 */
    int flags;                          /* +0x004 */
    VecFx32 carried;                    /* +0x008 */
    VecFx32 walk;                       /* +0x014 */
    VecFx32 slide;                      /* +0x020 */
    VecFx32 push;                       /* +0x02c */
    fx32 speedY;                        /* +0x038 */
    fx32 gravity;                       /* +0x03c */
    fx32 maxFall;                       /* +0x040 */
    s16 height;                         /* +0x044 */
    s16 active;                         /* +0x046 */
    HitRecord floorHit;                 /* +0x048 */
    VecFx32 floorPt;                    /* +0x0e0 */
    int floorState;                     /* +0x0ec */
    char pad0f0[0x43c - 0xf0];
    fx32 timer;                         /* +0x43c */
} Mover;

extern const VecFx32 data_02041dc8;     /* {0, 0, 0} */
extern const s16 data_0203d210[];       /* sin/cos pairs */

extern void *func_0202bfa0(u16 index);  /* collision world */
extern HitRecord *func_01fff7a4(void *world, CollCastParams *params);
extern void func_01ffd0e8(fx32 t, const VecFx32 *dir, const VecFx32 *origin, VecFx32 *out);
extern void func_02028d74(void *model, char *face, VecFx32 *normal);
extern Rider *func_01fffde0(int index);
extern int func_020293a8(FloorObject *obj);     /* sliding floor? */
extern int func_02023c40(void);         /* frame-rate mode */
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_MultAdd(fx32 a, const VecFx32 *v1, const VecFx32 *v2, VecFx32 *pDest);
extern fx32 func_01ff8d18(const VecFx32 *pSrc, VecFx32 *pDst);      /* VEC_Normalize */
extern void func_01ffa724(fx32 scale, const VecFx32 *v, VecFx32 *out);  /* scale a vector */

static inline fx32 MulRound(fx32 a, fx32 b) { return (fx32)(((s64)a * b + 0x800) >> 12); }

static inline void VEC_Set(VecFx32 *vec, fx32 x, fx32 y, fx32 z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

int func_0202cf64(VecFx32 *pos, Mover *mover, fx32 *fall)
{
    HitRecord snapshot;
    VecFx32 base;
    VecFx32 normal = data_02041dc8;
    CollCastParams params;
    VecFx32 origin2;
    VecFx32 dir;
    VecFx32 bestPt;
    VecFx32 offset;
    VecFx32 origin;
    VecFx32 hitPt;
    VecFx32 away;
    VecFx32 ledge;
    VecFx32 feet;
    VecFx32 hitPt2;
    VecFx32 slideDir;
    VecFx32 zero = data_02041dc8;
    int ret = 0;
    int found = 0;
    fx32 best = 0x80000000;
    fx32 lift = 0xb33;
    void *world;
    fx32 radius;
    int angle;
    int i;
    int count;
    int steep;
    HitRecord *hit;

    if (mover->active < 0) {
        return 0;
    }
    world = func_0202bfa0(mover->active);
    if (mover->height >= 0xb33) {
        lift = mover->height + 0x19a;
    }
    VEC_Set(&dir, 0, 0 - 0x50000, 0);
    count = 0;
    mover->floorState = 0;
    base.x = pos->x;
    base.y = pos->y + lift;
    base.z = pos->z;
    steep = 0;
    angle = mover->owner->angle;
    radius = 0x900;
    origin = zero;
    if (mover->owner->radius > 0xd00) {
        radius = mover->owner->radius - 10;
    }
    offset.x = MulRound(data_0203d210[(angle >> 4) * 2], radius);
    offset.y = 0;
    offset.z = MulRound(data_0203d210[(angle >> 4) * 2 + 1], radius);
    params.origin = &origin;
    params.direction = &dir;
    bestPt.x = bestPt.y = bestPt.z = 0;
    params.flags = 0;
    params.directionIsUnit = 1;
    params.exclude = mover->owner;
    for (i = 0; i < 5; i++) {
        VEC_Add(&origin, &base, &origin);
        hit = func_01fff7a4(world, &params);
        if (hit != 0) {
            hitPt.x = hitPt.y = hitPt.z = 0;
            func_01ffd0e8(hit->distance, &dir, &origin, &hitPt);
            if (pos->y + mover->height < hitPt.y) {
                continue;
            }
            if (best <= hitPt.y) {
                if (best < hitPt.y - 0x1ccd) {
                    count = 0;
                    steep = 0;
                }
                count++;
                if (best <= hitPt.y - 0x1ccd) {
                    if (!steep) {
                        bestPt = hitPt;
                        best = hitPt.y;
                        snapshot = *hit;
                    }
                    if (i == 0) {
                        found = 1;
                        func_02028d74(hit->model, hit->face + 0x14, &normal);
                        if (normal.y < 0xf33) {
                            steep = 1;
                        }
                    }
                    origin2 = origin;
                }
            }
        }
        origin = offset;
        offset.x = -origin.z;
        offset.z = origin.x;
    }
    if (!(mover->flags & 0x40) && count == 1 && (mover->flags & 4) && !(mover->flags & 2)) {
        ledge = bestPt;
        feet = *pos;
        ledge.y = 0;
        feet.y = 0;
        VEC_Subtract(&feet, &ledge, &away);
        func_01ff8d18(&away, &away);
        VEC_MultAdd(0x400, &away, &mover->walk, &mover->walk);
        mover->flags |= 0x100;
    } else {
        mover->walk.x = mover->walk.y = mover->walk.z = 0;
    }
    if (!(mover->flags & 0x400)) {
        mover->flags &= ~4;
    }
    if (found) {
        int height = mover->height;
        fx32 prevFall = *fall;
        int snap;
        int onPlatform;
        fx32 dropOffset;
        int slid;
        int carried;
        FloorObject *obj;
        fx32 floorY;

        params.origin = &origin2;
        carried = slid = dropOffset = onPlatform = snap = 0;
        params.directionIsUnit = 0;
        hit = func_01fff7a4(world, &params);
        if (hit != 0) {
            func_01ffd0e8(hit->distance, &dir, &origin2, &hitPt2);
            bestPt = hitPt2;
            if (best > bestPt.y) {
                bestPt.y = best;
            }
            snapshot = *hit;
        }
        obj = snapshot.obj;
        if (obj != 0) {
            mover->floorState = 1;
            floorY = bestPt.y;
            if (pos->y - floorY < 0x400) {
                int k;
                FloorNode *node = obj->node;

                if (node->moving == 0) {
                    onPlatform = 1;
                    dropOffset = -0x800;
                    for (k = 0; k < 4; k++) {
                        Rider *rider = func_01fffde0(k);

                        if (rider != 0 && node == rider->node) {
                            rider->flags |= 0x1000;
                            rider->floorPt = bestPt;
                            carried = 1;
                            if (*fall > 0) {
                                *fall = 0;
                            }
                        }
                    }
                }
                if (func_020293a8(obj)) {
                    mover->flags &= ~4;
                    mover->speedY = 0;
                    func_02028d74(snapshot.model, snapshot.face + 0x14, &normal);
                    if (!(mover->flags & 0x80)) {
                        if (normal.x == 0 && normal.z == 0) {
                            int angle = mover->owner->angle >> 4;

                            slideDir.y = 0;
                            slideDir.x = -data_0203d210[angle * 2];
                            slideDir.z = -data_0203d210[angle * 2 + 1];
                            func_01ff8d18(&slideDir, &slideDir);
                            VEC_Add(&normal, &slideDir, &slideDir);
                        } else {
                            slideDir = normal;
                        }
                        slideDir.y = 0;
                        func_01ff8d18(&slideDir, &slideDir);
                        func_01ffa724(func_02023c40() == 1 ? 0x400 : 0xb00, &slideDir, &mover->slide);
                        mover->timer = 0x1800;
                    }
                    if (carried) {
                        if (best > pos->y) {
                            pos->y = best;
                        }
                    } else if (floorY > pos->y) {
                        pos->y = floorY;
                    }
                    slid = 1;
                    mover->flags |= 0x80;
                }
            }
        }
        if (!slid) {
            if (!onPlatform) {
                mover->floorPt = bestPt;
                mover->floorState = 2;
                mover->floorHit = snapshot;
            }
            {
                fx32 y = pos->y;
                fx32 d = bestPt.y - y;

                if (d < 0) {
                    d = -d;
                }
                if (d < height && *fall == (fx32)0x80000000) {
                    snap = 1;
                }
                if (prevFall == (fx32)0x80000000) {
                    prevFall = 0;
                }
                if ((prevFall != 0 && dropOffset + (y + prevFall) <= bestPt.y) || snap) {
                    ret = 1;
                    if (carried) {
                        if (best > y) {
                            pos->y = best;
                        }
                    } else {
                        pos->y = bestPt.y;
                    }
                    mover->speedY = 0x80000000;
                    mover->flags |= 4;
                    mover->slide.x = mover->slide.y = mover->slide.z = 0;
                    mover->flags &= ~0x80;
                }
            }
        }
    }
    return ret;
}
