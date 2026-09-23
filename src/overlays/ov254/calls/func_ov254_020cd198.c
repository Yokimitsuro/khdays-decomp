/* Rebound hit test: sweeps the actor list with the given sphere or segment; every entity whose +2 id
 * bit is clear in the +0x71 mask is pushed 2.0 horizontally away from the actor (the +z axis of
 * data_02042258 when directly above; kind 3 lifts it by 1.0 instead of scaling). On acceptance the
 * actor spawns effect 0 at the rebound point (the volume's surface or segment end, pushed out) and the
 * entity's bit joins the result. The hits are added to the mask and, if any, reaction 0 mode 0x50
 * fires at the +8 point. Returns the new hit bits. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;

extern const Vec3 data_02042258;
extern int func_ov107_020c8eb8(int owner, void *sphere, int *hits);
extern int func_ov107_020c8f44(int owner, void *seg, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const void *a, const void *b, void *out);
extern int func_ov107_020ca918(int hit, int owner, int item, u8 kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);

u8 func_ov254_020cd198(int *state, int kind, Vec3 *sphere, Segment *seg)
{
    int n = 0;
    u8 hitMask = 0;
    int hits[4];
    Vec3 push;
    Vec3 dir;
    Vec3 end;
    int i;

    if (sphere != 0) {
        n = func_ov107_020c8eb8(*state, sphere, hits);
    } else if (seg != 0) {
        n = func_ov107_020c8f44(*state, seg, hits);
    }
    for (i = 0; i < n; i++) {
        u8 bit = 1 << *(u16 *)(hits[i] + 2);

        if ((*((u8 *)state + 0x71) & bit) != 0) {
            continue;
        }
        VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push);
        func_01ff8d18(&push, &dir);
        push.y = 0;
        if (func_01ff8d18(&push, &push) == 0) {
            push = data_02042258;
        }
        if (kind == 3) {
            push.y = 0x1000;
        } else {
            func_01ffa724(0x2000, &push, &push);
        }
        if (func_ov107_020ca918(hits[i], *state, *state, kind, &push, 0) == 0) {
            continue;
        }
        if (sphere != 0) {
            func_01ffa724(*(int *)((u8 *)sphere + 0xc), &dir, &dir);
            VEC_Add(&dir, sphere, &dir);
        } else {
            func_01ffa724(seg->nLength, &seg->dir, &end);
            VEC_Add(&end, seg, &end);
            VEC_Add(&dir, &end, &dir);
        }
        VEC_Add(&dir, &push, &dir);
        func_ov107_020c0b90(*state, 0, dir, 0);
        hitMask |= bit;
    }
    *((u8 *)state + 0x71) |= hitMask;
    if (hitMask != 0) {
        func_ov107_020c5af8(*state, 0, 0x50, (void *)state[2]);
    }
    return hitMask;
}
