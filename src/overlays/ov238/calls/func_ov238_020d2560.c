/* Landing tick of the ov238 actor: +0x20 accumulates the frame rate, the +0xc velocity follows the
 * +0x3e0 part's +0x2c vector turned by the heading and sound 0x12e/0xa cues after 15 frames; once the
 * partner holds no queued move pose 0 loops, bits 0-1 of +0x1ae are set and the +0x38c shape hides. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern void func_ov238_020d07f0(int *node, Vec3 *vec);
extern void func_ov238_020d0f0c(int *node, int ticks, int cue, int variant);
extern void func_ov107_020c9264(int actor, int pose, int loop);

void func_ov238_020d2560(int *node)
{
    int *state = (int *)node[1];

    state[8] += *(int *)(node[0] + 0x2c);
    func_ov238_020d07f0(node, (Vec3 *)(*(int *)(*state + 0x3e0) + 0x2c));
    func_ov238_020d0f0c(node, 0xf, 2, 0xa);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0, 1);
    *(u16 *)(*state + 0x1ae) |= 3;
    ((B8 *)(*(int *)(*state + 0x38c) + 8))->f &= ~1;
}
