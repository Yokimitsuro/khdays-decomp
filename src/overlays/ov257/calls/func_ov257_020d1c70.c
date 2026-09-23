/* Jump start tick of an ov257 state: the +0x40 rate is the frame rate x 3, the nearest target
 * (020cab14) becomes +0x60 and the +0x10 step heads for it (func_ov257_020ccf98). The +0x54 timer
 * accumulates the frame rate and at 0.33 reaction +0x408 mode 0x1b fires once at the +4 point
 * (+0x76). Once the +0xc idle byte clears the +0x64 jump velocity is set: towards the target on
 * the flat, as long as a 50th of the distance, and 1.0 up less a 50th of it (at least 1/16);
 * without a target just 1/16 up. Animation 0x1d and the +0x3d0 part's motion 0x1a play looped and
 * the tick hands over to func_ov257_020d1e24. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int obj, int *out);
extern int func_ov257_020ccf98(int *state, int target, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov257_020d1e24(int *node);

void func_ov257_020d1c70(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    Vec3 d;
    int speed;
    int found;

    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 10;
    state[0x18] = func_ov107_020cab14(*state, &found);
    func_ov257_020ccf98(state, state[0x18], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    state[0x15] += *(int *)(node[0] + 0x2c);
    if (*((unsigned char *)state + 0x76) == 0 && state[0x15] >= 0x555) {
        func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0x1b, (void *)state[1]);
        *((unsigned char *)state + 0x76) = 1;
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    if (state[0x18] != 0) {
        VEC_Subtract((void *)(state[0x18] + 0x74), (void *)(*state + 0x74), &d);
        d.y = 0;
        func_01ff8d18(&d, (Vec3 *)(state + 0x19));
        func_01ffa724(VEC_Mag(&d) / 50, (Vec3 *)(state + 0x19), (Vec3 *)(state + 0x19));
        state[0x1a] = 0x1000 - VEC_Mag(&d) / 50;
        if (state[0x1a] < 0x100) {
            state[0x1a] = 0x100;
        }
    } else {
        state[0x19] = 0;
        state[0x1a] = 0x100;
        state[0x1b] = 0;
    }
    func_ov107_020c9264(*state, 0x1d, 1);
    func_ov107_020c9ee8(*(int *)(*state + 0x3d0), 0x1a, 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov257_020d1e24);
}
