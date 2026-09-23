/* Bite tick of an ov257 state: a two-phase trigger on the rig's channel-0 frame (+0x78) fires
 * reaction +0x408 mode 1 at the +8 point once it reaches 6.0 and rearms below it. The +0x40 rate is
 * the frame rate x 3; without a nearest target (020cab14, kept in +0x60) sub-state 2 is requested,
 * otherwise the +0x10 step heads for it (func_ov257_020ccf98) and, once the +0xc idle byte clears,
 * sub-state 2 is requested as well. */
typedef struct { int x, y, z; } Vec3;

extern int func_0203bec0(int rig, int channel);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int func_ov107_020cab14(int obj, int kind);
extern int func_ov257_020ccf98(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov257_020cdf10(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;

    {
        unsigned char phase = *((unsigned char *)state + 0x78);

        if (phase == 0) {
            if (func_0203bec0(*(int *)(*state + 0x384), 0) >= 0x6000) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 1, (void *)state[2]);
                *((unsigned char *)state + 0x78) = 1;
            }
        } else if (phase == 1) {
            if (func_0203bec0(*(int *)(*state + 0x384), 0) < 0x6000) {
                *((unsigned char *)state + 0x78) = 0;
            }
        }
    }
    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 10;
    state[0x18] = func_ov107_020cab14(*state, 0);
    if (state[0x18] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_ov257_020ccf98(state, state[0x18], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
