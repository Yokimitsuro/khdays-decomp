/* Slam charge tick of the ov259 actor: the ground test (020cdc20) and aim refresh run; within three
 * body radii (+0x80) the x/z drift decays to a quarter. The +0x68 timer accumulates the frame rate
 * and the cue pulses at 0x330 (bit 0, 2) and at 0xaa0 on the first step / 0xee0 on the second
 * (bit 1, 3). Once the partner holds no queued move: a target beyond 12 radii queues move 0x12,
 * beyond 5 move 0x10, and the node ends; otherwise the first step (+0x98 == 0) plays pose 0x13
 * sweeping 0x550-0xee0 and restarts, and the second plays pose 0x14 sweeping 0x330-0x550, resets the
 * step and moves on to 020d06b0 (+0x420 = 5 both times). */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern int func_ov259_020cdc20(int *node);
extern void func_ov259_020cdcac(int *node);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_ov259_020cd2c8(int actor, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov259_020cd524(int *node, int pose, int mode);
extern void func_ov259_020d1700(int body, int a, int b, Vec3 lift);
extern void func_ov259_020d06b0(void);
extern const Vec3 data_02041dc8;

void func_ov259_020d0400(int *node)
{
    int *state = (int *)node[1];
    int ground = func_ov259_020cdc20(node);
    Vec3 v;

    func_ov259_020cdcac(node);
    if (ground <= *(int *)(*state + 0x80) * 3) {
        v = *(Vec3 *)(state + 5);
        func_01ffa724(0x400, &v, &v);
        state[5] = v.x;
        state[7] = v.z;
    }
    state[0x1a] += *(int *)(node[0] + 0x2c);
    switch (state[0x26]) {
    case 0:
        if ((*((u8 *)state + 0xac) & 1) == 0 && state[0x1a] >= 0x330) {
            *((u8 *)state + 0xac) |= 1;
            func_ov259_020cd2c8(*state, 2);
        }
        if ((*((u8 *)state + 0xac) & 2) == 0 && state[0x1a] >= 0xaa0) {
            *((u8 *)state + 0xac) |= 2;
            func_ov259_020cd2c8(*state, 3);
        }
        break;
    case 1:
        if ((*((u8 *)state + 0xac) & 1) == 0 && state[0x1a] >= 0x330) {
            *((u8 *)state + 0xac) |= 1;
            func_ov259_020cd2c8(*state, 2);
        }
        if ((*((u8 *)state + 0xac) & 2) == 0 && state[0x1a] >= 0xee0) {
            *((u8 *)state + 0xac) |= 2;
            func_ov259_020cd2c8(*state, 3);
        }
        break;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (ground > *(int *)(*state + 0x80) * 12) {
        *(signed char *)(*state + 0x1c7) = 0x12;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (ground > *(int *)(*state + 0x80) * 5) {
        *(signed char *)(*state + 0x1c7) = 0x10;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0x26] == 0) {
        func_ov107_020c9264(*state, 0x13, 0);
        func_ov259_020cd524(node, 0x13, 0);
        func_ov259_020d1700(*(int *)(*state + 0x384), 0x550, 0xee0, data_02041dc8);
        *(int *)(*state + 0x420) = 5;
        state[0x26]++;
        *((u8 *)state + 0xac) = 0;
        state[0x1a] = 0;
        return;
    }
    func_ov107_020c9264(*state, 0x14, 0);
    func_ov259_020cd524(node, 0x14, 0);
    func_ov259_020d1700(*(int *)(*state + 0x384), 0x330, 0x550, data_02041dc8);
    *(int *)(*state + 0x420) = 5;
    state[0x26] = 0;
    *((u8 *)state + 0xac) = 0;
    state[0x1a] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020d06b0);
}
