/* Update of the ov258 shot effect: its rig clears flag 1 and the +0x14 age runs up at the frame rate;
 * at 0xaa0 the pending +0x19 launch sound (0x8 of the owner's bank) plays at the +8 point. From 0xe58 to
 * 0x1430, while the owner is in move 1, a 48.0-long upright capsule of radius 0.875 pushes every target
 * it touches once (+0x18 mask) away from the centre (a vertical offset spread sideways) at 0.5, kind 2,
 * with sound 0xe and effect 0x16. Once the owner's rig is idle the owner's effect slot 0xc + the +0x1a
 * index is released and the node ends (0203c640). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; Vec3 axis; int length; int radius; } Capsule;
struct EffectPair { int res; int handle; };
struct Ov258Effects { char pad[0x464]; struct EffectPair pair[0x30]; };

extern void func_ov107_020c5af8(int actor, short bank, int variant, void *at);
extern int func_ov107_020c8f44(int owner, void *capsule, int *hits);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, u8 kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c640(int *node);
extern const Vec3 data_02042264;

void func_ov258_020d0800(int *node)
{
    int *state = (int *)node[1];
    int hits[4];
    Capsule cap;
    Vec3 push;
    long i;
    long n;
    u8 bit;

    *(int *)(state[0] + 0x5c) &= ~2;
    state[5] += *(int *)(node[0] + 0x2c);
    if (state[5] >= 0xaa0 && *((u8 *)state + 0x19) != 0) {
        *((u8 *)state + 0x19) = 0;
        func_ov107_020c5af8(state[1], *(int *)(state[1] + 0x460) != 0 ? 0x180 : 0x17b, 8, state + 2);
    }
    if (state[5] >= 0xe58 && state[5] < 0x1430 && *(int *)(state[1] + 0x50) == 1) {
        cap.pos = *(Vec3 *)(state + 2);
        cap.axis = data_02042264;
        cap.length = 0x30000;
        cap.radius = 0xe00;
        n = func_ov107_020c8f44(state[1], &cap, hits);
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
            if (*((u8 *)state + 0x18) & bit) {
                continue;
            }
            if (func_ov107_020ca918(hits[i], state[1], state[1], 2, &push, 0) == 0) {
                continue;
            }
            func_ov107_020c5af8(state[1], *(int *)(state[1] + 0x460) != 0 ? 0x180 : 0x17b, 0xe, state + 2);
            func_ov107_020c0b90(state[1], 0x16, *(Vec3 *)(hits[i] + 0x190), 0);
            *((u8 *)state + 0x18) |= bit;
        }
    }
    if (*(u8 *)(state[0] + 0xad) != 0) {
        return;
    }
    ((struct Ov258Effects *)state[1])->pair[*((signed char *)state + 0x1a) + 0xc].handle = 0;
    func_0203c640(node);
}
