/* Step cue of the ov258 actor: once the +0x44 clock reaches `step` x 0x88 and the +0x53 low-nibble
 * countdown is at `phase`, the countdown steps down and (for variants below 0x1b) sound variant
 * `variant` of the +0x58 bank plays at the +0x430 rig's +0x14 point. */
typedef unsigned char u8;
typedef struct { u8 lo : 4; u8 hi : 4; } NibblePair;

extern void func_ov107_020c5af8(int actor, int bank, int variant, int at);

void func_ov258_020cd6c8(int *node, int step, int phase, unsigned int variant)
{
    int *state = (int *)node[1];

    if (state[0x11] < step * 0x88) {
        return;
    }
    if (phase != ((NibblePair *)((u8 *)state + 0x53))->lo) {
        return;
    }
    if (variant >= 0x1b) {
        ((NibblePair *)((u8 *)state + 0x53))->lo--;
        return;
    }
    ((NibblePair *)((u8 *)state + 0x53))->lo--;
    func_ov107_020c5af8(*state, *(short *)(state + 0x16), variant, *(int *)(*state + 0x430) + 0x14);
}
