/* d0bbc */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 center; int nRadius; } Sphere;

extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c640(int *node);

void func_ov258_020d0bbc(int *node)
{
    int *state = (int *)node[1];
    int hits[4];
    Sphere sphere;
    Vec3 push;
    long i;
    long n;
    u8 bit;

    *(int *)(*state + 0x5c) &= ~2;
    state[5] += *(int *)(node[0] + 0x2c);
    if (*(int *)(state[1] + 0x50) == 1 && state[5] < 0xaa0) {
        sphere.center = *(Vec3 *)(state + 2);
        sphere.nRadius = 0x3000;
        n = func_ov107_020c8eb8(state[1], &sphere, hits);
        for (i = 0; i < n; i++) {
            bit = 1 << *(u16 *)(hits[i] + 2);

            VEC_Subtract((void *)(hits[i] + 0x190), state + 2, &push);
            func_01ff8d18(&push, &push);
            if (push.y != 0) {
                int half = push.y / 2;

                push.y = 0;
                push.x += half;
                push.z += half;
            }
            func_01ffa724(0x800, &push, &push);
            push.z += 0x3000;
            push.y += 0x1000;
            if ((*((u8 *)state + 0x18) & bit) != 0) {
                continue;
            }
            if (func_ov107_020ca918(hits[i], state[1], state[1], 3, &push, 0) == 0) {
                continue;
            }
            func_ov107_020c5af8(state[1], (short)(*(int *)(state[1] + 0x460) != 0 ? 0x180 : 0x17b), 0x10,
                                (void *)(hits[i] + 0x190));
            func_ov107_020c0b90(state[1], 7, *(Vec3 *)(hits[i] + 0x190), 0);
            *((u8 *)state + 0x18) |= bit;
        }
    }
    if (*(u8 *)(*state + 0xad) != 0) {
        return;
    }
    *(int *)(state[1] + (*((signed char *)state + 0x1a) + 0x1b) * 8 + 0x468) = 0;
    func_0203c640(node);
}
