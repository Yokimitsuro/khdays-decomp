/* Tick of an ov252 gem shot: its model's +0x5c bit 1 clears and +0x30 accumulates the frame rate; the
 * nearest target (020cab14) goes to +8, and without one the layers fade (mode 2) and the node moves on
 * to 020d38e8. The shot homes on the target until 0.81 (or while unlocked, +0x35), then keeps the
 * locked +0x24 heading; it moves at 1.0 (+0x35 = 1), 0.375 (+0x38 big) or 0.1875. In phase 1 its
 * 2.0 sphere pushes targets up and away (020ca918 kind 1) with sound 0x148/9 and effect 1, flipping
 * the shot's bit in the spawner's +0x57c mask; hitting ground or walls flips it too. The model follows
 * the shot, a pending +0x36 start plays the layers (mode 1, 1), and past its range (2.5 / 5.75 / 3.5)
 * the bit flips, +0x3c is set and effect 1 plays. With the bit clear the layers fade and the node moves
 * on to 020d38e8. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 center; int nRadius; } Sphere;

extern int func_ov107_020cab14(int actor, int *distOut);
extern void func_0203b9fc(int rig, int channel, int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern int func_01fff920(int grid, void *pos, void *vel);
extern int func_01fff948(int grid, void *pos, void *vel, int radius);
extern void func_0203ca30(void *srt, const Vec3 *v);
extern void func_ov252_020d38e8(void);

void func_ov252_020d346c(int *node)
{
    int *state = (int *)node[1];
    Vec3 aim;
    int hits[4];
    Sphere sphere;
    Vec3 push;
    signed char i;
    int n;
    int owner;
    int speed;
    int range;

    *(int *)(*state + 0x5c) &= ~2;
    state[0xc] += *(int *)(node[0] + 0x2c);
    state[2] = func_ov107_020cab14(state[1], 0);
    if (state[2] == 0) {
        func_0203b9fc(*state, 0, 2, 0);
        func_0203b9fc(*state, 2, 2, 0);
        func_0203b9fc(*state, 4, 2, 0);
        func_0203b9fc(*state, 1, 2, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d38e8);
        return;
    }
    VEC_Subtract((Vec3 *)(state[2] + 0x190), (Vec3 *)(state + 3), &aim);
    func_01ff8d18(&aim, &aim);
    if (state[0xc] < 0xd00 || *((u8 *)state + 0x35) == 0) {
        *(Vec3 *)(state + 6) = aim;
        *(Vec3 *)(state + 9) = aim;
    } else {
        *(Vec3 *)(state + 6) = *(Vec3 *)(state + 9);
    }
    speed = *((u8 *)state + 0x35) == 1 ? 0x1000 : (state[0xe] != 0 ? 0x600 : 0x300);
    func_01ffa724(speed, (Vec3 *)(state + 6), (Vec3 *)(state + 6));
    VEC_Add((Vec3 *)(state + 3), (Vec3 *)(state + 6), (Vec3 *)(state + 3));
    if (*(int *)(state[1] + 0x50) == 1) {
        sphere.center = *(Vec3 *)(state + 3);
        sphere.nRadius = 0x2000;
        n = func_ov107_020c8eb8(state[1], &sphere, hits);
        for (i = 0; i < n; i++) {
            VEC_Subtract((Vec3 *)(hits[i] + 0x190), (Vec3 *)(state + 3), &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            func_01ffa724(0x800, &push, &push);
            push.y += 0x1000;
            if (func_ov107_020ca918(hits[i], state[1], state[1], 1, &push, 0) != 0) {
                func_ov107_020c5af8(state[1], 0x148, 9, state + 3);
                func_ov107_020c0b90(state[1], 1, *(Vec3 *)(state + 3), 0);
                *(u16 *)(state[1] + 0x57c) ^= 1 << *((signed char *)state + 0x34);
            }
        }
    }
    owner = *(int *)(state[1] + 4);
    if (func_01fff920(*(int *)(owner + 0x7c), state + 3, state + 6) != 0) {
        *(u16 *)(state[1] + 0x57c) ^= 1 << *((signed char *)state + 0x34);
    }
    if (func_01fff948(*(int *)(owner + 0x7c), state + 3, state + 6, 0x2000) != 0) {
        *(u16 *)(state[1] + 0x57c) ^= 1 << *((signed char *)state + 0x34);
    }
    func_0203ca30((void *)(*state + 4), (Vec3 *)(state + 3));
    if (*(u8 *)(*state + 0xad) == 0 && *((u8 *)state + 0x36) != 0) {
        *((u8 *)state + 0x36) = 0;
        func_0203b9fc(*state, 0, 1, 1);
        func_0203b9fc(*state, 2, 1, 1);
        func_0203b9fc(*state, 4, 1, 1);
        func_0203b9fc(*state, 1, 1, 1);
    }
    range = *((u8 *)state + 0x35) == 1 ? 0x2800 : (state[0xe] != 0 ? 0x5c00 : 0x3800);
    if (state[0xc] >= range) {
        *(u16 *)(state[1] + 0x57c) ^= 1 << *((signed char *)state + 0x34);
        state[0xf] = 1;
        func_ov107_020c0b90(state[1], 1, *(Vec3 *)(state + 3), 0);
    }
    if (*(u16 *)(state[1] + 0x57c) & (1 << *((signed char *)state + 0x34))) {
        return;
    }
    func_0203b9fc(*state, 0, 2, 0);
    func_0203b9fc(*state, 2, 2, 0);
    func_0203b9fc(*state, 4, 2, 0);
    func_0203b9fc(*state, 1, 2, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d38e8);
}
