/* Stomp tick of the ov258 actor: the +0x30 and +0x44 clocks run up at the frame rate with six step
 * cues (020cd6c8). At 2.99 (+0x50 = 3) and 3.98 (+0x50 = 2) a stomp arms the +0x458 / +0x45c hand
 * window, at 4.81 (+0x50 = 1) the +0x458 hand again. Each of the four stomps (+0x3c count, landing at
 * 2.29, 3.32, 4.22 and 4.98) drops its data_ov258_020d182c marker turned by the +0x28 heading at 15.6
 * height (effect 8 / 9 alternating, kept in +0x1c), and for 1/3 after landing an upright cylinder 0.5
 * above it (radius 12.0 / 6.0 alternating) hits once with push data_ov258_020d1820 (kind 1); between
 * stomps the +0x52 low mask clears. Each time the +4 rig finishes a remaining stomp (+0x52 high nibble)
 * replays pose 0xb (last) or 0xe with effect 3 or 4; with none left a follow-up (020cd2cc, without a
 * +0x38 delay) or move 2 follows. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct { Vec3 pos; Vec3 axis[3]; int radius; int flag; } Cylinder;
typedef struct { u8 lo : 4; u8 hi : 4; } NibblePair;

extern void func_ov258_020cd6c8(int *node, int step, int phase, u16 variant);
extern void func_ov258_020cfd3c(int partner, int from, int to, int d);
extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const Vec3 *pIn, const Mtx33 *pMtx, Vec3 *pOut);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern int func_ov258_020cd104(int *node, void *sphere, void *box, void *capsule, void *cylinder, Vec3 *push, int once, u16 effect, int kind);
extern void func_ov107_020c9264(int a, int b, int c);
extern int func_ov258_020cd2cc(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const Vec3 data_ov258_020d1820;
extern const Vec3 data_ov258_020d182c;
extern const Vec3 data_02041dc8;
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;
extern const Vec3 data_02042270;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov258_020ce0a0(int *node)
{
    int *state = (int *)node[1];
    Vec3 marker;
    Mtx33 rot;
    Cylinder cyl;
    Vec3 push;

    state[0xc] += *(int *)(node[0] + 0x2c);
    state[0x11] += *(int *)(node[0] + 0x2c);
    func_ov258_020cd6c8(node, 0x3e, 6, *(int *)(*state + 0x460) != 0 ? 0x1b : 0x12);
    func_ov258_020cd6c8(node, 0x40, 5, 3);
    func_ov258_020cd6c8(node, 0x60, 4, 5);
    func_ov258_020cd6c8(node, 0x78, 3, *(int *)(*state + 0x460) != 0 ? 0x1b : 0x11);
    func_ov258_020cd6c8(node, 0x7a, 2, 4);
    func_ov258_020cd6c8(node, 0x92, 1, 5);
    if ((state[0xc] >= 0x2fd0 && *(u16 *)(state + 0x14) == 3) || (state[0xc] >= 0x3fc0 && *(u16 *)(state + 0x14) == 2)) {
        (*(u16 *)(state + 0x14))--;
        if (state[0xc] < 0x3fc0) {
            func_ov258_020cfd3c(*(int *)(*state + 0x458), 0x2a8, 0x550, 1);
        } else {
            func_ov258_020cfd3c(*(int *)(*state + 0x45c), 0x2a8, 0x550, 1);
        }
    }
    if (state[0xc] >= 0x4d08 && *(u16 *)(state + 0x14) == 1) {
        (*(u16 *)(state + 0x14))--;
        func_ov258_020cfd3c(*(int *)(*state + 0x458), 0x110, 0x550, 1);
    }
    if ((state[0xf] == 0 && state[0xc] >= 0x24a8) || (state[0xf] == 1 && state[0xc] >= 0x3520) ||
        (state[0xf] == 2 && state[0xc] >= 0x4378) || (state[0xf] == 3 && state[0xc] >= 0x4fb0)) {
        marker = data_ov258_020d182c;
        {
            int idx = ANG2IDX(state[0xa]) * 2;

            MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
        }
        MTX_MultVec33(&marker, &rot, &marker);
        marker.y = 0xfa00;
        if (++state[0xf] % 2 == 1) {
            func_ov107_020c0b90(*state, 8, marker, 0);
        } else {
            func_ov107_020c0b90(*state, 9, marker, 0);
        }
        *(Vec3 *)(state + 7) = marker;
    }
    if ((state[0xc] >= 0x24a8 && state[0xc] < 0x24a8 + 0x550) || (state[0xc] >= 0x3520 && state[0xc] < 0x3520 + 0x550) ||
        (state[0xc] >= 0x4378 && state[0xc] < 0x4378 + 0x550) || (state[0xc] >= 0x4fb0 && state[0xc] < 0x5500)) {
        push = data_ov258_020d1820;
        cyl.pos = *(Vec3 *)(state + 7);
        cyl.pos.y += 0x800;
        cyl.axis[0] = data_02042270;
        cyl.axis[1] = data_02042258;
        cyl.axis[2] = data_02042264;
        cyl.radius = state[0xf] % 2 == 0 ? 0xc000 : 0x6000;
        cyl.flag = 1;
        func_ov258_020cd104(node, 0, 0, 0, &cyl, &push, 1, 0, 1);
    } else {
        ((NibblePair *)((u8 *)state + 0x52))->lo = 0;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (((NibblePair *)((u8 *)state + 0x52))->hi != 0) {
        ((NibblePair *)((u8 *)state + 0x52))->hi--;
        func_ov107_020c9264(*state, ((NibblePair *)((u8 *)state + 0x52))->hi == 1 ? 0xb : 0xe, 0);
        func_ov107_020c0b90(*state, ((NibblePair *)((u8 *)state + 0x52))->hi == 1 ? 3 : 4, data_02041dc8, 0);
        return;
    }
    if (state[0xe] == 0 && func_ov258_020cd2cc(node) != 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    *(signed char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
