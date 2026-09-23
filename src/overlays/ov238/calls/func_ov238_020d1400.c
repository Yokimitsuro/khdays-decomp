/* Swipe tick of the ov238 actor: +0x20 accumulates the frame rate, sounds 0x12e/5 and 0x12e/4 cue after
 * 10 and 18 frames, the +0xc velocity follows the +0x3e0 part's +0x2c vector turned by the heading;
 * once the partner holds no queued move the next move is 4 (with +0x28 set and +0x2e not 1), else 2. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov238_020d0f0c(int *node, int ticks, int cue, int variant);
extern void func_ov238_020d07f0(int *node, Vec3 *vec);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov238_020d1400(int *node)
{
    int *state = (int *)node[1];

    state[8] += *(int *)(node[0] + 0x2c);
    func_ov238_020d0f0c(node, 0xa, 2, 5);
    func_ov238_020d0f0c(node, 0x12, 1, 4);
    func_ov238_020d07f0(node, (Vec3 *)(*(int *)(*state + 0x3e0) + 0x2c));
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (*((unsigned char *)state + 0x2e) == 1 || state[0xa] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
    } else {
        *(unsigned char *)(*state + 0x1c7) = 4;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
