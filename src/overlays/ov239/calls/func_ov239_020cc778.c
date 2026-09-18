/* Contact sweep of the ov239 enemy: collects the entities in the given sphere (else the actor's
 * own +0x74/+0x80 sphere) and, for each whose id bit is clear in the +0x30 mask, offers a hit of
 * the given kind pushed 0x800 away from the actor on the ground plane (forward when on top of
 * it); on acceptance effect 3 spawns at the sphere surface along the push and the id bit is set.
 * When anything was hit, reaction 0x138 mode 6 fires at the +8 point. */
typedef unsigned char u8;
typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;

extern int func_ov107_020c8eb8(int actor, Sphere *sphere, int *out);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020ca918(int hit, int a, int b, u8 kind, Vec3 *push, int z);
extern void VEC_Add(void *a, void *b, Vec3 *d);
extern void func_ov107_020c0b90(int actor, int a, Vec3 v, int b);
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern const Vec3 data_02042258;

void func_ov239_020cc778(int *state, int kind, Sphere *sphere)
{
    int hit;
    Sphere probe;
    int hits[4];
    Vec3 push;
    Vec3 dir;
    Vec3 fwd;
    long i;
    long n;
    unsigned int mask;

    hit = 0;
    if (sphere != 0) {
        probe = *sphere;
    } else {
        probe.pos = *(Vec3 *)(*state + 0x74);
        probe.radius = *(int *)(*state + 0x80);
    }
    n = func_ov107_020c8eb8(*state, &probe, hits);
    i = 0;
    if (n > 0) {
        fwd = data_02042258;
        do {
            mask = (1 << *(unsigned short *)(hits[i] + 2)) & 0xff;
            if ((*(u8 *)(state + 0xc) & mask) == 0) {
                VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push);
                func_01ff8d18(&push, &dir);
                push.y = 0;
                if (func_01ff8d18(&push, &push) == 0) {
                    push = fwd;
                }
                func_01ffa724(0x800, &push, &push);
                if (func_ov107_020ca918(hits[i], *state, *state, kind, &push, 0) != 0) {
                    func_01ffa724(probe.radius, &dir, &dir);
                    VEC_Add(&dir, &push, &dir);
                    VEC_Add(&dir, &probe, &dir);
                    func_ov107_020c0b90(*state, 3, dir, 0);
                    *(u8 *)(state + 0xc) |= mask;
                    hit = 1;
                }
            }
        } while (++i < n);
    }
    if (hit != 0) {
        func_ov107_020c5af8(*state, 0x138, 6, (void *)state[2]);
    }
}
