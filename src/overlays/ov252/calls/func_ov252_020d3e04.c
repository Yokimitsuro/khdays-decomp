/* Tick of an ov252 gem: its model's +0x5c bit 1 clears and +0x20 accumulates the frame rate; once its
 * part stops animating the first time, layers 0, 2, 4 and 1 play (mode 3, 1). While the spawner is in
 * phase 1 and after 0.23, a box around the gem (1.5 x 7.5 x scale x 1.5, raised 6.84 x scale) hits
 * targets: each is pushed away at 0.5 (020ca918 kind 4), the spawner plays effect 0x11 on it and sound
 * 0/0x53 at the gem, and the gem's bit in the spawner's +0x57e mask flips. The mask bit also flips for
 * every live bomb (+0x714 pairs) closer than 1.5, after 16.0, or when the spawner is within 10.0.
 * With the bit clear the layers fade (mode 4), the spawner plays effect 6 at the gem and the node moves
 * on to 020d4204. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 center; Vec3 axisX; Vec3 axisY; Vec3 axisZ; int nExtentX; int nExtentY; int nExtentZ; } Box;
struct BombPair { int obj; int active; };
struct Ov252Spawner { char pad[0x714]; struct BombPair pair[12]; };

extern void func_0203b9fc(int rig, int channel, int a, int b);
extern int func_ov107_020c8df0(int owner, Box *box, int *hits);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d4204(void);
extern const Vec3 data_02042270;
extern const Vec3 data_02042264;
extern const Vec3 data_02042258;

void func_ov252_020d3e04(int *node)
{
    int *state = (int *)node[1];
    int hits[4];
    Box box;
    Vec3 push;
    Vec3 diff;
    Vec3 other;
    Vec3 d;
    Vec3 me;
    signed char i;
    int n;
    signed char j;
    int dist;

    *(int *)(*state + 0x5c) &= ~2;
    state[8] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0x26) == 0 && *(u8 *)(*state + 0xad) == 0) {
        *((u8 *)state + 0x26) += 1;
        func_0203b9fc(*state, 0, 3, 1);
        func_0203b9fc(*state, 2, 3, 1);
        func_0203b9fc(*state, 4, 3, 1);
        func_0203b9fc(*state, 1, 3, 1);
    }
    if (*(int *)(state[1] + 0x50) == 1 && state[8] >= 0x3b8) {
        box.center = *(Vec3 *)(state + 2);
        box.center.y += (state[6] / 0x1000) * 0x6d80;
        box.axisX = data_02042270;
        box.axisY = data_02042264;
        box.axisZ = data_02042258;
        box.nExtentX = 0x1800;
        box.nExtentY = (state[6] / 0x1000) * 0x7800;
        box.nExtentZ = 0x1800;
        n = func_ov107_020c8df0(state[1], &box, hits);
        for (i = 0; i < n; i++) {
            VEC_Subtract((Vec3 *)(hits[i] + 0x190), (Vec3 *)(state + 2), &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            func_01ffa724(0x800, &push, &push);
            if (func_ov107_020ca918(hits[i], state[1], state[1], 4, &push, 0) != 0) {
                func_ov107_020c0b90(state[1], 0x11, *(Vec3 *)(hits[i] + 0x190), 0);
                func_ov107_020c5af8(state[1], 0, 0x53, state + 2);
                *(u16 *)(state[1] + 0x57e) ^= 1 << *((signed char *)state + 0x24);
            }
        }
    }
    for (j = 0; j < 12; j++) {
        if (((struct Ov252Spawner *)state[1])->pair[j].active != 0) {
            other = *(Vec3 *)(((struct Ov252Spawner *)state[1])->pair[j].obj + 0x14);
            other.y = state[3];
            VEC_Subtract(&other, (Vec3 *)(state + 2), &diff);
            if (func_01ff8d18(&diff, &diff) < 0x1800) {
                *(u16 *)(state[1] + 0x57e) ^= 1 << *((signed char *)state + 0x24);
            }
        }
    }
    me = *(Vec3 *)(state + 2);
    me.y = *(int *)(state[1] + 0xb4);
    VEC_Subtract((Vec3 *)(state[1] + 0xb0), &me, &d);
    dist = func_01ff8d18(&d, &d);
    if (state[8] >= 0x10000 || dist < 0xa000) {
        *(u16 *)(state[1] + 0x57e) ^= 1 << *((signed char *)state + 0x24);
    }
    if (*(u16 *)(state[1] + 0x57e) & (1 << *((signed char *)state + 0x24))) {
        return;
    }
    func_0203b9fc(*state, 0, 4, 0);
    func_0203b9fc(*state, 2, 4, 0);
    func_0203b9fc(*state, 4, 4, 0);
    func_0203b9fc(*state, 1, 4, 0);
    func_ov107_020c0b90(state[1], 6, *(Vec3 *)(state + 2), 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d4204);
}
