/* Roar tick of the ov238 actor: +0x20 accumulates the frame rate, the cues play sound 0x12e/5 after 5
 * frames and 0x12e/4 after 15, the +0xc velocity follows the +0x3e0 part's +0x2c vector turned by the
 * heading (020d07f0); once the partner holds no queued move the next move is 2 and the node ends. */
typedef struct { int x, y, z; } Vec3;

extern void func_ov238_020d0f0c(int *node, int ticks, int cue, int variant);
extern void func_ov238_020d07f0(int *node, Vec3 *vec);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov238_020d244c(int *node)
{
    int *state = (int *)node[1];

    state[8] += *(int *)(node[0] + 0x2c);
    func_ov238_020d0f0c(node, 5, 2, 5);
    func_ov238_020d0f0c(node, 0xf, 1, 4);
    func_ov238_020d07f0(node, (Vec3 *)(*(int *)(*state + 0x3e0) + 0x2c));
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
