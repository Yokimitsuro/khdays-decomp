/* Sweep of the ov221 enemy's strike: the entities inside the given sphere are tested one by
 * one -- each whose +2 id bit is clear in the +0x64 mask is pushed 1.0 along the flattened
 * unit direction from the owner's +0x74 (kind +0x58 byte) and, on acceptance, the sphere's
 * centre goes out as the mode-0 message (func_ov225_020d4784), reaction 0x14b
 * mode 8 fires at the +8 point and the bit is set. Returns the entity count. */
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int nRadius; } Sphere;

extern int func_ov107_020c8eb8(int owner, Sphere *query, int *out);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *a, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, Vec3 *push, int z);
extern void func_ov225_020d4784(int *state, Vec3 v, int flag);
struct Ov221Byte8 { unsigned int lo : 8, rest : 24; };
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);

int func_ov225_020d47cc(int *node, Sphere *sphere)
{
    int *state = (int *)node[1];
    int hits[4];
    Vec3 push;
    long i;
    long n;
    unsigned char bit;

    n = func_ov107_020c8eb8(*state, sphere, hits);
    i = 0;
    if (n > 0) {
        do {
            bit = 1 << *(unsigned short *)(hits[i] + 2);
            if ((*(unsigned char *)((char *)state + 0x64) & bit) == 0) {
                VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push);
                push.y = 0;
                func_01ff8d18(&push, &push);
                func_01ffa724(0x1000, &push, &push);
                if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x390), state[0x16] & 0xff, &push, 0) != 0) {
                    func_ov225_020d4784(state, sphere->pos, 0);
                    func_ov107_020c5af8(*state, 0x14b, 8, (void *)state[2]);
                    *(unsigned char *)((char *)state + 0x64) |= bit;
                }
            }
        } while (++i < n);
    }
    return n;
}
