/* Combo tick of the ov259 actor: the +0x68 timer accumulates the frame rate, the ground test
 * (020cdc20) and aim refresh run and the drift decays to a quarter while within the body radius
 * (+0x80). When the step time (+0x80) runs out, the partner holds no queued move or the combo has not
 * started (+0x98 == 0), the next swing plays on the actor and its partner: 0 pose 9 sweeping
 * 0x440-0x660 for 0x7f8, 1 pose 0xa sweeping 0x880-0xbb0 for 0xcc0, 2 pose 0xb sweeping 0x220-0x440
 * for 0x13a8 with +0x424 set (+0x420 = 0 each time); the timer restarts and the step count grows.
 * After the third swing the node moves on to 020cef48. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern int func_ov259_020cdc20(int *node);
extern void func_ov259_020cdcac(int *node);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov259_020cd524(int *node, int pose, int mode);
extern void func_ov259_020d1700(int body, int a, int b, Vec3 lift);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020cef48(void);
extern const Vec3 data_02041dc8;

void func_ov259_020ced2c(int *node)
{
    int *state = (int *)node[1];
    int next = 0;
    int ground;

    state[0x1a] += *(int *)(node[0] + 0x2c);
    ground = func_ov259_020cdc20(node);
    func_ov259_020cdcac(node);
    if (ground <= *(int *)(*state + 0x80)) {
        func_01ffa724(0x400, (Vec3 *)(state + 5), (Vec3 *)(state + 5));
    }
    if (state[0x1a] > state[0x20] || *(u8 *)(state[1] + 0xad) == 0 || state[0x26] == 0) {
        next = 1;
    }
    if (next == 0) {
        return;
    }
    switch (state[0x26]) {
    case 0:
        func_ov107_020c9264(*state, 9, 0);
        func_ov259_020cd524(node, 9, 0);
        func_ov259_020d1700(*(int *)(*state + 0x384), 0x440, 0x660, data_02041dc8);
        *(int *)(*state + 0x420) = 0;
        state[0x20] = 0x7f8;
        break;
    case 1:
        func_ov107_020c9264(*state, 0xa, 0);
        func_ov259_020cd524(node, 0xa, 0);
        func_ov259_020d1700(*(int *)(*state + 0x384), 0x880, 0xbb0, data_02041dc8);
        *(int *)(*state + 0x420) = 0;
        state[0x20] = 0xcc0;
        break;
    case 2:
        func_ov107_020c9264(*state, 0xb, 0);
        func_ov259_020cd524(node, 0xb, 0);
        func_ov259_020d1700(*(int *)(*state + 0x384), 0x220, 0x440, data_02041dc8);
        *(int *)(*state + 0x420) = 0;
        state[0x20] = 0x13a8;
        *(int *)(*state + 0x424) = 1;
        break;
    default:
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020cef48);
        return;
    }
    state[0x1a] = 0;
    state[0x26]++;
}
