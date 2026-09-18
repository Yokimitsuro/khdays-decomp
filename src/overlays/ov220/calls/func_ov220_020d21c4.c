/* Attack sweep of the ov220 enemy: sweeps the actor's +0x74 sphere and, for every entity whose
 * id bit (1 << its +2 id, as a byte) is clear in the +0x3c mask, pushes it away on the ground
 * plane by 0x800 (falling back to the shared forward vector) through the ov107 checker with the
 * given kind. On acceptance the contact point (the actor's position plus the radius along the
 * unflattened direction plus the push) is published with mode 0 and the id bit is set. Reaction
 * 0x137 mode 5 fires at the +8 position when anything was hit; returns whether it did. */
typedef unsigned char u8;
typedef unsigned short u16;
struct Vecx32 { int x, y, z; };
struct Sphere { struct Vecx32 pos; int radius; };

extern int func_ov107_020c8eb8(int owner, struct Sphere *sphere, int *out);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern void func_01ffa724(int scale, void *v, void *d);
extern int func_ov107_020ca918(int hit, int actor, int item, u8 kind, void *push, int z);
extern void VEC_Add(void *a, void *b, void *d);
extern void func_ov107_020c0b90(int actor, int a, struct Vecx32 v, int b);
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern const struct Vecx32 data_02042258;

int func_ov220_020d21c4(int *state, int kind)
{
    struct Sphere sphere;
    int hits[4];
    struct Vecx32 push;
    struct Vecx32 out;
    struct Vecx32 fwd;
    int hit;
    long i;
    long n;
    u8 mask;

    sphere.pos = *(struct Vecx32 *)(*state + 0x74);
    sphere.radius = *(int *)(*state + 0x80);
    hit = 0;
    n = func_ov107_020c8eb8(*state, &sphere, hits);
    i = 0;
    if (n > 0) {
        fwd = data_02042258;
        do {
            mask = (u8)(1 << *(u16 *)(hits[i] + 2));
            if ((*(u8 *)((char *)state + 0x3c) & mask) == 0) {
                VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push);
                func_01ff8d18(&push, &out);
                push.y = 0;
                if (func_01ff8d18(&push, &push) == 0) {
                    push = fwd;
                }
                func_01ffa724(0x800, &push, &push);
                if (func_ov107_020ca918(hits[i], *state, *state, kind, &push, 0) != 0) {
                    func_01ffa724(sphere.radius, &out, &out);
                    VEC_Add(&out, &push, &out);
                    VEC_Add(&out, &sphere.pos, &out);
                    func_ov107_020c0b90(*state, 0, out, 0);
                    *(u8 *)((char *)state + 0x3c) |= mask;
                    hit = 1;
                }
            }
        } while (++i < n);
    }
    if (hit != 0) {
        func_ov107_020c5af8(*state, 0x137, 5, (void *)state[2]);
    }
    return hit;
}
