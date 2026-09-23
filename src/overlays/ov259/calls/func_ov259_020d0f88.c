/* Charge tick of the ov259 actor: it keeps facing its target (020cd5d4) while the +0x68 timer
 * accumulates the frame rate; the cue pulses once 0x330 before the end (020cd2c8 2, +0xac bit 0).
 * Past 0x27d8 the timer, cue flags and +0x60 clear, +0x38 resets, +0x2c takes the target's +0x190
 * point, pose 0x18 loops on the actor and its partner and the node moves on to 020d105c. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_ov259_020cd5d4(int *node);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov259_020cd524(int *node, int pose, int mode);
extern void func_ov259_020cd2c8(int actor, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov259_020d105c(void);
extern const Vec3 data_02041dc8;

void func_ov259_020d0f88(int *node)
{
    int *state = (int *)node[1];

    func_ov259_020cd5d4(node);
    state[0x1a] += *(int *)(node[0] + 0x2c);
    if (state[0x1a] > 0x27d8) {
        state[0x1a] = 0;
        *((u8 *)state + 0xac) = 0;
        state[0x18] = 0;
        *(Vec3 *)(state + 0xe) = data_02041dc8;
        *(Vec3 *)(state + 0xb) = *(Vec3 *)(state[2] + 0x190);
        func_ov107_020c9264(*state, 0x18, 1);
        func_ov259_020cd524(node, 0x18, 1);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov259_020d105c);
        return;
    }
    if ((*((u8 *)state + 0xac) & 1) == 0 && state[0x1a] >= 0x27d8 - 0x330) {
        *((u8 *)state + 0xac) |= 1;
        func_ov259_020cd2c8(*state, 2);
    }
}
