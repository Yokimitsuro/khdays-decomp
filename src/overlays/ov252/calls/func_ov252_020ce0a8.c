/* Rebound hit test: sweeps the actor list with the given box, cylinder or sphere (in that order of
 * preference); kind 6 uses the +0x85 hit mask, others +0x86. Every entity whose +2 id bit is clear
 * in the mask is pushed horizontally away from the actor (the +z axis when directly above): kind 3 by
 * 0.94, kind 6 by 1.0 at a 2.5 lift, others by 0.5 (kind 5 lifted by 3.3, kind 1 by 2.0). On
 * acceptance the actor spawns effect 0 at the rebound point (the entity pushed out, or the sphere's
 * surface) and the entity's bit joins the result. The hits are added to the mask; returns the new
 * hit bits. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern const Vec3 data_02042258;
extern int func_ov107_020c8df0(int owner, void *box, int *hits);
extern int func_ov107_020c8fd0(int owner, void *cyl, int *hits);
extern int func_ov107_020c8eb8(int owner, void *sphere, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const void *a, const void *b, void *out);
extern int func_ov107_020ca918(int hit, int owner, int item, u8 kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);

u8 func_ov252_020ce0a8(int *state, int kind, Vec3 *sphere, void *cyl, void *box)
{
    int n = 0;
    u8 *mask = kind == 6 ? (u8 *)state + 0x85 : (u8 *)state + 0x86;
    u8 hitMask = 0;
    int hits[4];
    Vec3 push;
    Vec3 dir;
    int i;

    if (box != 0) {
        n = func_ov107_020c8df0(*state, box, hits);
    } else if (cyl != 0) {
        n = func_ov107_020c8fd0(*state, cyl, hits);
    } else if (sphere != 0) {
        n = func_ov107_020c8eb8(*state, sphere, hits);
    }
    for (i = 0; i < n; i++) {
        u8 bit = 1 << *(u16 *)(hits[i] + 2);

        if ((*mask & bit) != 0) {
            continue;
        }
        VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push);
        func_01ff8d18(&push, &dir);
        push.y = 0;
        if (func_01ff8d18(&push, &push) == 0) {
            push = data_02042258;
        }
        if (kind == 5) {
            push.y += 0x3500;
        }
        if (kind == 1) {
            push.y += 0x2000;
        }
        if (kind == 3) {
            func_01ffa724(0xf00, &push, &push);
        } else if (kind == 6) {
            push.y = 0x2800;
            func_01ffa724(0x1000, &push, &push);
        } else {
            func_01ffa724(0x800, &push, &push);
        }
        if (func_ov107_020ca918(hits[i], *state, *state, kind, &push, 0) == 0) {
            continue;
        }
        if (box != 0 || cyl != 0) {
            VEC_Add((void *)(hits[i] + 0x74), &push, &dir);
            func_ov107_020c0b90(*state, 0, dir, 0);
        } else if (sphere != 0) {
            func_01ffa724(*(int *)((u8 *)sphere + 0xc), &dir, &dir);
            VEC_Add(&dir, &push, &dir);
            VEC_Add(&dir, sphere, &dir);
            func_ov107_020c0b90(*state, 0, dir, 0);
        }
        hitMask |= bit;
    }
    *mask |= hitMask;
    return hitMask;
}
