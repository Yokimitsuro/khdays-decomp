/* Contact sweep of the ov276 enemy: collects the entities in the given box (or else sphere) and,
 * for each whose id bit is clear in the +0x62 mask, offers a hit of the given kind pushed 0x800
 * away from the +0x474 point on the ground plane (forward when on top of it); on acceptance
 * effect 4 spawns at the entity pushed out of the box, or effect 1 at the sphere surface along
 * the push, and the id bit is set. When anything was hit, reaction 0x164 mode 5 (kinds 0/5),
 * mode 6 (kind 1) or reaction 0 mode 0x53 (kind 2) fires at the +0xc position. */
typedef unsigned char u8;
typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;

extern int func_ov107_020c8fd0(int actor, void *box, int *out);
extern int func_ov107_020c8eb8(int actor, Sphere *sphere, int *out);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020ca918(int hit, int a, int b, u8 kind, Vec3 *push, int z);
extern void VEC_Add(void *a, void *b, Vec3 *d);
extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern const Vec3 data_02042258;

void func_ov276_020d0954(int *state, int kind, Sphere *sphere, void *box)
{
    int hits[4];
    Vec3 push;
    Vec3 dir;
    Vec3 fwd;
    int n;
    int hit;
    int i;
    unsigned int mask;

    n = 0;
    hit = 0;
    if (box != 0) {
        n = func_ov107_020c8fd0(*state, box, hits);
    } else if (sphere != 0) {
        n = func_ov107_020c8eb8(*state, sphere, hits);
    }
    i = 0;
    if (n > 0) {
        fwd = data_02042258;
        do {
            mask = (1 << *(unsigned short *)(hits[i] + 2)) & 0xff;
            if ((*(u8 *)((char *)state + 0x62) & mask) == 0) {
                VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x474), &push);
                func_01ff8d18(&push, &dir);
                push.y = 0;
                if (func_01ff8d18(&push, &push) == 0) {
                    push = fwd;
                }
                func_01ffa724(0x800, &push, &push);
                if (func_ov107_020ca918(hits[i], *state, *state, kind, &push, 0) != 0) {
                    if (box != 0) {
                        VEC_Add((void *)(hits[i] + 0x74), &push, &dir);
                        func_ov107_020c0b90(*state, 4, dir, 0);
                    } else if (sphere != 0) {
                        func_01ffa724(sphere->radius, &dir, &dir);
                        VEC_Add(&dir, &push, &dir);
                        VEC_Add(&dir, sphere, &dir);
                        func_ov107_020c0b90(*state, 1, dir, 0);
                    }
                    *(u8 *)((char *)state + 0x62) |= mask;
                    hit = 1;
                }
            }
        } while (++i < n);
    }
    if (hit == 0) {
        return;
    }
    switch (kind) {
    case 0:
    case 5:
        func_ov107_020c5af8(*state, 0x164, 5, (void *)state[3]);
        break;
    case 1:
        func_ov107_020c5af8(*state, 0x164, 6, (void *)state[3]);
        break;
    case 2:
        func_ov107_020c5af8(*state, 0, 0x53, (void *)state[3]);
        break;
    case 3:
    case 4:
        break;
    }
}
