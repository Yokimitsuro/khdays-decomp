/* Slam tick of the ov258 actor: the +0x30 and +0x44 clocks run up at the frame rate with a step cue at
 * 0x36 x 0x88. At 2.49 the pending slam (+0x50 = 2) lands on the target: a 3.0 sphere at its +0x190
 * point hits once with a 2.0 forward push (effect 7, kind 5), effect 0x28 and the slam sounds play
 * there; in move 7 it also starts the vortex once (+0x54 bit 3: +0x1c point (0, 15.6, 8.0), effect
 * 0x2a, 5.6 of vortex time, sound 0x12/0x19). At 4.45 the follow-through (+0x50 = 1) plays effect 0x29
 * at the +0x5a4 rig. Once the +4 rig is idle: before 3.98 pose 0xd replays; move 7 continues with
 * 020cf63c; otherwise a follow-up (020cd2cc, without a +0x38 delay) or move 2. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;

extern void func_ov258_020cd6c8(int *node, int step, int phase, u16 variant);
extern int func_ov258_020cd104(int *node, void *sphere, void *box, void *capsule, void *cylinder, Vec3 *push, int once, u16 effect, int kind);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int actor, int bank, u16 variant, int at);
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_ov258_020cd2cc(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov258_020cf63c(void);
extern const Vec3 data_02041dc8;

void func_ov258_020cf324(int *node)
{
    int *state = (int *)node[1];
    Sphere sphere;
    Vec3 push;

    state[0xc] += *(int *)(node[0] + 0x2c);
    state[0x11] += *(int *)(node[0] + 0x2c);
    func_ov258_020cd6c8(node, 0x36, 3, *(int *)(*state + 0x460) != 0 ? 0x1b : 0x13);
    if (*(u16 *)(state + 0x14) == 2 && state[0xc] >= 0x27d8) {
        push = data_02041dc8;
        push.z += 0x2000;
        sphere.pos = *(Vec3 *)(*(int *)(*state + 0x454) + 0x190);
        sphere.radius = 0x3000;
        (*(u16 *)(state + 0x14))--;
        func_ov258_020cd104(node, &sphere, 0, 0, 0, &push, 1, 7, 5);
        func_ov107_020c0b90(*state, 0x28, *(Vec3 *)(*(int *)(*state + 0x454) + 0x190), 0);
        func_ov107_020c5af8(*state, *(short *)(state + 0x16), *(int *)(*state + 0x460) != 0 ? 0x11 : 0x18,
                            *(int *)(*state + 0x454) + 0x190);
        func_ov107_020c5af8(*state, 0, 0x4f, *(int *)(*state + 0x454) + 0x190);
        if (*(signed char *)(*state + 0x1c6) == 7 && !(*((u8 *)state + 0x54) & 8)) {
            *((u8 *)state + 0x54) |= 8;
            state[7] = 0;
            state[8] = 0xfa00;
            state[9] = 0x8000;
            func_ov107_020c0b90(*state, 0x2a, *(Vec3 *)(state + 7), 0);
            *(int *)(*state + 0x428) = 0x5a00;
            func_ov107_020c5af8(*state, *(short *)(state + 0x16), *(int *)(*state + 0x460) != 0 ? 0x12 : 0x19,
                                (int)(state + 7));
        }
    }
    if (state[0xc] >= 0x4730 && *(u16 *)(state + 0x14) == 1) {
        (*(u16 *)(state + 0x14))--;
        func_ov107_020c0b90(*state, 0x29, *(Vec3 *)(*(int *)(*state + 0x5a4) + 0x14), 0);
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0xc] < 0x3fc0) {
        func_ov107_020c9264(*state, 0xd, 0);
        return;
    }
    if (*(signed char *)(*state + 0x1c6) == 7) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov258_020cf63c);
        return;
    }
    if (state[0xe] == 0 && func_ov258_020cd2cc(node) != 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    *(signed char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
