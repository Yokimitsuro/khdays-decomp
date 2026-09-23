/* Double-slam tick of the ov237 actor: the +0x30 clock runs up at the frame rate; at 0.46 (first
 * slam, +0x34 = 0) and 1.49 (second, +0x34 = 1) the impact point is that +0x42c hand 1.31 lower,
 * with effect 2 and the slam sound (0x12d variant 4); for 0.6 after each a 1.0 x 0.19 box there hits
 * once with push data_ov237_020d1bac. Every frame the last two segments of both arms (+0x3f4) sweep
 * with push data_ov237_020d1ba0 (radius 0.375). The +0x3c aim point follows the +0x3d8 partner; once
 * the +4 rig is idle poses 9 / partner 5 play and the brain waits on 020cec58. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; Vec3 axis[3]; int ext[3]; } Box;
typedef struct { int w[7]; int radius; } Segment;
struct Arm { int parts[5]; };
struct Ov237Arms { char pad[0x3f4]; struct Arm arms[2]; char pad41c[0x10]; struct Arm hands[2]; };

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int actor, int bank, int variant, int at);
extern int func_ov237_020cdbe4(int *node, void *sphere, void *box, void *segment, Vec3 *push, int once, unsigned short effect, int kind);
extern Vec3 func_ov237_020cdb50(int *node, Vec3 *target);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c9ee8(int actor, int pose, int c);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov237_020cec58(void);
extern const Vec3 data_ov237_020d1ba0;
extern const Vec3 data_ov237_020d1bac;
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;
extern const Vec3 data_02042270;

void func_ov237_020ce980(int *node)
{
    int *state = (int *)node[1];
    Vec3 hand;
    Box box;
    Vec3 push;
    Segment seg;
    Vec3 sweep;
    Vec3 aim;
    Vec3 sweepPush;
    int k;
    int m;

    state[0xc] += *(int *)(node[0] + 0x2c);
    if ((state[0xc] >= 0x770 && state[0xd] == 0) || (state[0xc] >= 0x17e8 && state[0xd] == 1)) {
        hand = *(Vec3 *)(((struct Ov237Arms *)*state)->hands[state[0xd]].parts[0] + 0x14);
        hand.y -= 0x1500;
        func_ov107_020c0b90(*state, 2, hand, 0);
        func_ov107_020c5af8(*state, 0x12d, 4, state[0xe]);
        *(Vec3 *)(state + 0x12) = hand;
        state[0xd]++;
    }
    if ((state[0xc] >= 0x6e8 && state[0xc] < 0x6e8 + 0x990) ||
        (state[0xc] >= 0x17e8 && state[0xc] < 0x17e8 + 0x990)) {
        push = data_ov237_020d1bac;
        box.pos = *(Vec3 *)(state + 0x12);
        box.axis[0] = data_02042270;
        box.axis[1] = data_02042264;
        box.axis[2] = data_02042258;
        box.ext[0] = 0x1000;
        box.ext[1] = 0x300;
        box.ext[2] = 0x1000;
        func_ov237_020cdbe4(node, 0, &box, 0, &push, 1, 0, 0);
    }
    sweepPush = data_ov237_020d1ba0;
    for (k = 0; k < 2; k++) {
        for (m = 0; m < 5; m++) {
            sweep = sweepPush;
            if (m >= 3) {
                seg = *(Segment *)(((struct Ov237Arms *)*state)->arms[k].parts[m] + 0x78);
                seg.radius = 0x600;
                func_ov237_020cdbe4(node, 0, 0, &seg, &sweep, 0, 0, 0);
            }
        }
    }
    aim = func_ov237_020cdb50(node, (Vec3 *)(*(int *)(*state + 0x3d8) + 0x2c));
    *(Vec3 *)(state + 0xf) = aim;
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 9, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3d8), 5, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov237_020cec58);
}
