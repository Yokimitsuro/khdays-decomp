/* Wind-up tick of an ov235 state: a three-phase trigger on the rig's channel-0 frame (0203bec0)
 * -- at 1.0 reaction +0x3c8 mode 1 fires at the +8 point, at 11.0 mode 0, and once the frame falls
 * back below 11.0 the cycle restarts (+0x65). The +0x40 rate follows the frame rate; without a
 * nearest target (020cab14, kept in +0x5c) sub-state 2 is requested. Otherwise the +0x10 step
 * heads for it (func_ov235_020cccc0); once it is within 4.0 or the +0x4c cooldown has run out,
 * the rig's +0xa8 byte clears and the tick hands over to func_ov235_020ce000. */
typedef struct { int x, y, z; } Vec3;

extern int func_0203bec0(int rig, int channel);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int func_ov107_020cab14(int obj, int kind);
extern int func_ov235_020cccc0(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov235_020ce000(int *node);

void func_ov235_020cde6c(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;
    int dist;

    {
        unsigned char phase = *((unsigned char *)state + 0x65);

        if (phase == 0) {
            if (func_0203bec0(*(int *)(*state + 0x384), 0) >= 0x1000) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 1, (void *)state[2]);
                *((unsigned char *)state + 0x65) = 1;
            }
        } else if (phase == 1) {
            if (func_0203bec0(*(int *)(*state + 0x384), 0) >= 0xb000) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 0, (void *)state[2]);
                *((unsigned char *)state + 0x65) = 2;
            }
        } else if (phase == 2) {
            if (func_0203bec0(*(int *)(*state + 0x384), 0) < 0xb000) {
                *((unsigned char *)state + 0x65) = 0;
            }
        }
    }
    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 30;
    state[0x17] = func_ov107_020cab14(*state, 0);
    if (state[0x17] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    dist = func_ov235_020cccc0(state, state[0x17], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    if (dist > 0x4000 && state[0x13] > 0) {
        return;
    }
    *(unsigned char *)(*(int *)(*state + 0x384) + 0xa8) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov235_020ce000);
}
