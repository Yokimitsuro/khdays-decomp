/* Update of the ov258 burst effect: its rig clears flag 1 and the +0x14 age runs up at the frame rate.
 * While the owner is in move 1 and the burst is younger than 0xaa0, a 3.0 sphere at the +8 point
 * pushes every target it touches once (+0x18 mask): away from the centre (a vertical offset spread
 * sideways) at 0.5 with a 1.0 / 3.0 lift, kind 3; each hit plays sound 0x10 of the owner's bank and
 * effect 7. Once the owner's rig is idle the owner's effect slot 0x1b + the +0x1a index is released
 * and the node ends (0203c640). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;
struct EffectPair { int res; int handle; };
struct Ov258Effects { char pad[0x464]; struct EffectPair pair[0x30]; };

extern int func_ov107_020c8eb8(int owner, void *sphere, int *hits);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, u8 kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int actor, short bank, int variant, int at);
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

    *(int *)(state[0] + 0x5c) &= ~2;
    state[5] += *(int *)(node[0] + 0x2c);
    if (*(int *)(state[1] + 0x50) == 1 && state[5] < 0xaa0) {
        sphere.pos = *(Vec3 *)(state + 2);
        sphere.radius = 0x3000;
        n = func_ov107_020c8eb8(state[1], &sphere, hits);
        for (i = 0; i < n; i++) {
            bit = 1 << *(u16 *)(hits[i] + 2);
            VEC_Subtract((Vec3 *)(hits[i] + 0x190), (Vec3 *)(state + 2), &push);
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
            if (*((u8 *)state + 0x18) & bit) {
                continue;
            }
            if (func_ov107_020ca918(hits[i], state[1], state[1], 3, &push, 0) == 0) {
                continue;
            }
            func_ov107_020c5af8(state[1], *(int *)(state[1] + 0x460) != 0 ? 0x180 : 0x17b, 0x10, hits[i] + 0x190);
            func_ov107_020c0b90(state[1], 7, *(Vec3 *)(hits[i] + 0x190), 0);
            *((u8 *)state + 0x18) |= bit;
        }
    }
    if (*(u8 *)(state[0] + 0xad) != 0) {
        return;
    }
    ((struct Ov258Effects *)state[1])->pair[*((signed char *)state + 0x1a) + 0x1b].handle = 0;
    func_0203c640(node);
}
