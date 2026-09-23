/* Claw lob tick of the ov256 actor: the +0x4c timer accumulates the frame rate; at 0xcc0 the first
 * charge knocks it back at the +0xc point (mode 1), at 0x1ba0 the second knocks it back again (mode
 * 2) and the next claw of the +0x43c set (+0x54 counter) is thrown from 2.19 above that point
 * (020d0334). Once the partner holds no queued move, after boost + 1 claws (+0x45c) the next move is
 * the +0x74 mode + 2 and the node ends; otherwise the timer restarts with two charges and pose 9. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov256_020d0334(int claw, Vec3 *at);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov256_020cfc1c(int *node)
{
    int *state = (int *)node[1];
    Vec3 at;

    state[0x13] += *(int *)(node[0] + 0x2c);
    if (state[0x13] >= 0xcc0 && *((u8 *)state + 0x69) == 2) {
        *((u8 *)state + 0x69) -= 1;
        func_ov107_020c0b90(*state, 1, *(Vec3 *)state[3], 0);
    }
    if (state[0x13] >= 0x1ba0 && *((u8 *)state + 0x69) != 0) {
        at = *(Vec3 *)state[3];
        at.y += 0x2300;
        *((u8 *)state + 0x69) = 0;
        func_ov107_020c0b90(*state, 2, *(Vec3 *)state[3], 0);
        func_ov256_020d0334(*(int *)(*state + state[0x15] * 4 + 0x43c), &at);
        state[0x15]++;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0x15] == *(int *)(*state + 0x45c) + 1) {
        *(signed char *)(*state + 0x1c7) = state[0x1d] + 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0x13] = 0;
    *((u8 *)state + 0x69) = 2;
    func_ov107_020c9264(*state, 9, 0);
}
