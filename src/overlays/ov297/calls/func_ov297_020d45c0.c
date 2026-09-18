/* Orientation tick of the ov297 enemy: unless +0x88 locks it, the +0x2c yaw turns toward the
 * +0x30 target yaw by 90 frame-times over 10 (locked, it snaps); the actor's +0xa0 transform
 * takes the yaw as a quaternion about the up axis; the +0x3c timer counts the frame-time down
 * (clamped at 0); the +0x10 velocity moves to the actor's +0xf0 and is scaled by the +0x50
 * speed; the +0x40 and +0x58 timers count down while positive and the +0x94 flag mirrors
 * whether +0x58 still runs, resetting +0x78 when it changes. */
typedef struct { int x, y, z; } Vec3;

extern int func_0203d040(int cur, int target, int step, int *out);
extern void func_0202f188(int *quat, const Vec3 *axis, int angle);
extern void func_0203c9d0(void *srt, int *quat);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern const Vec3 data_02042264;

void func_ov297_020d45c0(int *node)
{
    int *state = (int *)node[1];
    int quat[4];
    int step;
    signed char was;
    Vec3 *vel;

    step = *(int *)(*node + 0x2c) * 0x5a / 10;
    was = *(signed char *)(state + 0x24);
    if (state[0x21] == 0) {
        state[0xb] = func_0203d040(state[0xb], state[0xc], step, 0);
    } else {
        state[0xb] = state[0xc];
    }
    func_0202f188(quat, &data_02042264, state[0xb]);
    func_0203c9d0((char *)*state + 0xa0, quat);
    state[0x10] -= *(int *)(*node + 0x2c);
    if (state[0x10] <= 0) {
        state[0x10] = 0;
    }
    vel = (Vec3 *)(state + 4);
    *(Vec3 *)(*state + 0xf0) = *vel;
    func_01ffa724(state[0x14], vel, vel);
    if (state[0x11] > 0) {
        state[0x11] -= *(int *)(*node + 0x2c);
    }
    if (state[0x16] > 0) {
        state[0x16] -= *(int *)(*node + 0x2c);
    }
    *(unsigned char *)(state + 0x24) = state[0x16] > 0;
    if (*(signed char *)(state + 0x24) != was) {
        state[0x1e] = 0;
    }
}
