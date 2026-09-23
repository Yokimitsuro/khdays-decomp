/* Burrow-burst tick: the +0x68 timer accumulates the frame rate; at 1/15 the +0xac flag bit 0 is
 * set and func_ov259_020cd2c8 plays animation 3. Until 0.5 a 2.0 sphere half a unit below the
 * actor's +0x74 point sweeps the actor list: every entity whose +2 id bit is clear in the +0xaf
 * mask is pushed 1.25 away horizontally (kind 3); on acceptance the actor spawns effect 0xb at its
 * +0x74 point and its bit is set. The mask then keeps only the entities still inside the sphere.
 * Once the +4 part's rig is idle (+0xad), pose 2 is requested. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 center; int nRadius; } Sphere;

extern void func_ov259_020cd2c8(int owner, int anim);
extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov259_020cf8e0(int *node)
{
    int *state = (int *)node[1];
    Sphere sphere;
    Vec3 push;
    int hits[4];
    int n;
    u16 i;
    u8 seen;

    state[0x1a] += *(int *)(node[0] + 0x2c);
    if ((*((u8 *)state + 0xac) & 1) == 0 && state[0x1a] >= 0x110) {
        *((u8 *)state + 0xac) |= 1;
        func_ov259_020cd2c8(*state, 3);
    }
    if (state[0x1a] < 0x7f8) {
        sphere.center = *(Vec3 *)(*state + 0x74);
        sphere.center.y -= 0x800;
        sphere.nRadius = 0x2000;
        seen = 0;
        n = func_ov107_020c8eb8(*state, &sphere, hits);
        for (i = 0; i < n; i++) {
            u8 bit = 1 << *(u16 *)(hits[i] + 2);

            seen |= bit;
            if ((*((u8 *)state + 0xaf) & bit) != 0) {
                continue;
            }
            VEC_Subtract((void *)(hits[i] + 0x74), &sphere.center, &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            func_01ffa724(0x1400, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *state, 3, &push, 0) == 0) {
                continue;
            }
            func_ov107_020c0b90(*state, 0xb, *(Vec3 *)(hits[i] + 0x74), 0);
            *((u8 *)state + 0xaf) |= bit;
        }
        *((u8 *)state + 0xaf) &= seen;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
