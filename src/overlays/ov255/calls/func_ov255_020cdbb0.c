/* Approach tick of an ov255 state: the +0x40 rate is the frame rate x 3 and the nearest target
 * (020cab14) becomes +0x5c; without one sub-state 2 is requested. Otherwise the path point is
 * resolved (func_ov255_020ccdac) into the +0x10 step and, once the +0xc idle byte clears, the
 * next sub-state is 0xc when the +0x54 cooldown has run out and the gap between the two collision
 * radii exceeds 4.0, else 2. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020cab14(int obj, int kind);
extern void func_ov255_020ccdac(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov255_020cdbb0(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    Vec3 d;
    int speed;

    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 10;
    state[0x17] = func_ov107_020cab14(*state, 0);
    if (state[0x17] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_ov255_020ccdac(state, state[0x17], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    {
        int target;
        int owner;
        int gap;

        owner = *state;
        target = state[0x17];

        VEC_Subtract((void *)(target + 0x74), (void *)(owner + 0x74), &d);
        gap = func_01ff8d18(&d, &d) - *(int *)(owner + 0x80) - *(int *)(target + 0x80);
        if (state[0x15] <= 0 && gap > 0x4000) {
            *(unsigned char *)(*state + 0x1c7) = 0xc;
        } else {
            *(unsigned char *)(*state + 0x1c7) = 2;
        }
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
