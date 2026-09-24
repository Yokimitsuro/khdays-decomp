/* func_0202da08 -- per-frame movement of a mover, MAIN. Returns 0 for an inactive mover (+0x46 < 0).
 * The recovery timer (+0x43c) drops by the frame step (0xcd at 30 fps, else 0x89) within 0..0x1800.
 * The displacement of the frame comes either from the push (+0x2c, taken out at most 0x200 per frame
 * unless the push flag 0x200 is set, and added to the carried velocity +0x08 unless it is) or from
 * the walk velocity (+0x14, at most 0x200 per frame, replaced by the slide +0x20 scaled by +-0x200 when
 * flag 0x80 is set; the carried velocity is cleared). A walk velocity used up clears flag 0x100. The
 * displacement is scaled by +0x438 when that is not 1.0, handed to the owner's collision
 * (func_0202c6c4, when `collide`) and added to the owner's position into `pos`. With gravity (flag 0x10)
 * the vertical speed (+0x38) is updated (gravity +0x3c at the frame rate, scaled by +0x438 while
 * falling, capped at -(+0x40)) and the frame's fall is resolved against floors and ceilings
 * (func_0202cf64 / func_0202d660, in falling or rising order); an unresolved fall moves pos.y. A
 * speed of 0x80000000 only snaps to the floor. Flags 0x40 and 0x1000 are cleared and 1 returned. */
typedef short s16;
typedef int fx32;
typedef long long s64;

typedef struct { fx32 x, y, z; } VecFx32;

typedef struct MoverOwner {
    char pad00[0xa8];
    VecFx32 pos;                        /* +0xa8 */
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
    short pad44;
    s16 active;                         /* +0x046 */
    char pad48[0x38c - 0x48];
    int field38c;                       /* +0x38c */
    char pad390[0x438 - 0x390];
    fx32 scale;                         /* +0x438 */
    fx32 timer;                         /* +0x43c */
} Mover;

extern const VecFx32 data_02041dc8;     /* {0, 0, 0} */

extern int func_02023c40(void);         /* frame-rate mode */
extern fx32 VEC_Mag(const VecFx32 *v);
extern fx32 func_01ff8d18(const VecFx32 *pSrc, VecFx32 *pDst);      /* VEC_Normalize, returns length */
extern void func_01ffa724(fx32 scale, const VecFx32 *v, VecFx32 *out);  /* scale a vector */
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_0202c6c4(VecFx32 *from, VecFx32 *disp, Mover *mover);
extern int func_0202cf64(VecFx32 *pos, Mover *mover, fx32 *fall);
extern int func_0202d660(VecFx32 *pos, Mover *mover, fx32 *fall);

#define FRAME_STEP() (func_02023c40() == 1 ? 0xcd : 0x89)
#define CLAMP(x, lo, hi) ((x) > (hi) ? (hi) : (x) < (lo) ? (lo) : (x))
#define FX_MUL(a, b) ((fx32)(((s64)(a) * (b) + 0x800) >> 12))

int func_0202da08(Mover *mover, VecFx32 *pos, int collide)
{
    VecFx32 disp = data_02041dc8;
    VecFx32 a;
    VecFx32 dir;
    VecFx32 b;
    VecFx32 dir2;
    VecFx32 zero = data_02041dc8;
    fx32 fall;
    MoverOwner *owner;

    if (mover->active < 0) {
        return 0;
    }
    mover->timer = CLAMP(mover->timer - FRAME_STEP(), 0, 0x1800);
    owner = mover->owner;
    mover->field38c = 0;
    mover->flags &= ~2;
    if ((mover->flags & 0x200) || (VEC_Mag(&mover->walk) == 0 && !(mover->flags & 0x80))) {
        fx32 limit;

        a = zero;
        limit = 0x200;
        if (VEC_Mag(&mover->push) != 0) {
            fx32 len = func_01ff8d18(&mover->push, &dir);

            if (!(mover->flags & 0x200)) {
                limit = len;
            }
            if (limit < len) {
                func_01ffa724(limit, &dir, &a);
                func_01ffa724(len - limit, &dir, &mover->push);
            } else {
                a = mover->push;
                mover->push.x = mover->push.y = mover->push.z = 0;
            }
        } else {
            mover->flags &= ~0x200;
        }
        if (mover->flags & 0x200) {
            disp = a;
        } else {
            VEC_Add(&mover->carried, &a, &disp);
        }
    } else {
        fx32 len;

        b = zero;
        len = func_01ff8d18(&mover->walk, &dir2);
        if (len > 0x200) {
            func_01ffa724(0x200, &dir2, &b);
            func_01ffa724(len - 0x200, &dir2, &mover->walk);
        } else {
            b = mover->walk;
            mover->walk.x = mover->walk.y = mover->walk.z = 0;
        }
        if (mover->flags & 0x80) {
            fx32 dirScale = 0x200;

            if (mover->timer <= 0) {
                dirScale -= 0x400;
            }
            func_01ffa724(dirScale, &mover->slide, &b);
        } else {
            mover->slide.x = mover->slide.y = mover->slide.z = 0;
        }
        disp = b;
        mover->carried.x = mover->carried.y = mover->carried.z = 0;
    }
    if (VEC_Mag(&mover->walk) == 0) {
        mover->flags &= ~0x100;
    }
    if (mover->scale != 0x1000) {
        func_01ffa724(mover->scale, &disp, &disp);
    }
    if (collide) {
        func_0202c6c4(&owner->pos, &disp, mover);
    }
    VEC_Add(&owner->pos, &disp, pos);
    if (mover->flags & 0x10) {
        if (mover->speedY != (fx32)0x80000000) {
            int hit;
            int k = func_02023c40() == 1 ? 0x1800 : 0x1000;
            fx32 g = FX_MUL(mover->gravity, k);

            hit = 0;
            if (mover->speedY < 0 && mover->scale != 0x1000) {
                g = FX_MUL(g, mover->scale);
            }
            fall = FX_MUL(mover->speedY, k);
            mover->speedY -= g;
            if (mover->speedY < -mover->maxFall) {
                mover->speedY = -mover->maxFall;
            }
            if (mover->speedY < 0) {
                if (func_0202cf64(pos, mover, &fall)) {
                    hit = 1;
                }
                if (func_0202d660(pos, mover, &fall)) {
                    hit = 1;
                }
            } else {
                if (func_0202d660(pos, mover, &fall)) {
                    hit = 1;
                }
                if (func_0202cf64(pos, mover, &fall)) {
                    hit = 1;
                }
            }
            if (!hit) {
                pos->y += fall;
            }
        } else {
            func_0202cf64(pos, mover, &mover->speedY);
        }
    }
    mover->flags &= ~0x40;
    mover->flags &= ~0x1000;
    return 1;
}
