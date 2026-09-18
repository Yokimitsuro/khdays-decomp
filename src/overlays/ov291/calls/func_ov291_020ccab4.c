/* Turn tick of the ov291 enemy: the +4 yaw turns towards the +8 target yaw by the +0x1c step
 * (d040), the actor's +0xa0 orientation becomes the quaternion of that yaw about the Y axis, the
 * +0x10 velocity moves to the actor's +0xf0 and is cleared. Unless the +0x30 flag is set, the
 * scene's +0xa8 list is walked: every entry whose +0x18c item has kind flag bit 16 clear counts;
 * one that cca78 accepts, while the +0x34 latch is clear, turns the ov022 handler on (86834 mode 1,
 * ov002 56a98 mode 1) and sets the latch. With nothing counted the latch and both are turned
 * off. */
typedef struct Vec3 { int x, y, z; } Vec3;

extern int func_0203d040(int cur, int want, int step, int mode);
extern void func_0202f188(int *quat, const Vec3 *axis, int angle);
extern void func_0203c9d0(void *orientation, int *quat);
extern int *func_01fffd70(int list);
extern int *func_01fffd8c(int list);
extern int func_ov022_02083f0c(void);
extern int func_ov022_02083f5c(void);
extern int func_ov291_020cca78(int item);
extern void func_ov022_02086834(int handle, int on);
extern void func_ov002_02056a98(int mode);
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;

void func_ov291_020ccab4(int *node)
{
    int *state = (int *)node[1];
    signed char count;
    int handle;
    int quat[4];
    int scene;
    int *entry;
    int other;
    Vec3 *vel;

    count = 0;
    state[1] = func_0203d040(state[1], state[2], state[7], 0);
    func_0202f188(quat, &data_02042264, state[1]);
    func_0203c9d0((void *)(*state + 0xa0), quat);
    vel = (Vec3 *)(state + 4);
    *(Vec3 *)(*state + 0xf0) = *vel;
    *vel = data_02041dc8;
    if (state[0xc] != 0) {
        return;
    }
    scene = *(int *)(*state + 4);
    entry = func_01fffd70(scene + 0xa8);
    other = entry == 0 ? 0 : *entry;
    while (other != 0) {
        if ((**(long long **)(other + 0x18c) & 0x10000) == 0) {
            func_ov022_02083f0c();
            handle = func_ov022_02083f5c();
            if (func_ov291_020cca78(*(int *)(other + 0x18c)) != 0 && state[0xd] == 0) {
                func_ov022_02086834(handle, 1);
                func_ov002_02056a98(1);
                state[0xd] = 1;
            }
            count++;
        }
        entry = func_01fffd8c(scene + 0xa8);
        other = entry == 0 ? 0 : *entry;
    }
    if (count != 0) {
        return;
    }
    state[0xd] = 0;
    func_ov022_02086834(handle, 0);
    func_ov002_02056a98(0);
}
