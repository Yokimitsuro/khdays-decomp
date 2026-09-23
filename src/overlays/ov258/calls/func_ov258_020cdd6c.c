/* Combo tick of the ov258 actor: the +0x30 and +0x44 clocks run up at the frame rate (the +0x30 clock
 * then restarts at 0.53 with a +0x460 partner, else 0) and six step cues fire along the combo
 * (020cd6c8). Each time the +4 rig finishes a remaining swing (+0x52 high nibble) is spent: the +0x50
 * counter drops, the clock clears, pose 10 (last swing) or 0xf plays with effect 2 (last) or 5 at the
 * origin and the +0x458 hand arms its 0.5 to 0.83 window; the final swing also arms the +0x45c hand.
 * With no swing left, without a +0x38 delay a follow-up (020cd2cc) may be picked, else the next move
 * is 2. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 lo : 4; u8 hi : 4; } NibblePair;

extern void func_ov258_020cd6c8(int *node, int step, int phase, u16 variant);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov258_020cfd3c(int partner, int from, int to, int d);
extern int func_ov258_020cd2cc(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02041dc8;

void func_ov258_020cdd6c(int *node)
{
    int *state = (int *)node[1];

    state[0xc] += *(int *)(node[0] + 0x2c);
    state[0x11] += *(int *)(node[0] + 0x2c);
    state[0xc] = *(int *)(*state + 0x460) != 0 ? 0x880 : 0;
    func_ov258_020cd6c8(node, 0x52, 6, *(int *)(*state + 0x460) != 0 ? 0x1b : 0x11);
    func_ov258_020cd6c8(node, 0x54, 5, 0);
    func_ov258_020cd6c8(node, 0x6e, 4, *(int *)(*state + 0x460) != 0 ? 0x1b : 0x12);
    func_ov258_020cd6c8(node, 0x70, 3, 1);
    func_ov258_020cd6c8(node, 0xb6, 2, *(int *)(*state + 0x460) != 0 ? 0x1b : 0x13);
    func_ov258_020cd6c8(node, 0xd2, 1, 2);
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (((NibblePair *)((u8 *)state + 0x52))->hi != 0) {
        ((NibblePair *)((u8 *)state + 0x52))->hi--;
        (*(u16 *)(state + 0x14))--;
        state[0xc] = 0;
        func_ov107_020c9264(*state, ((NibblePair *)((u8 *)state + 0x52))->hi == 1 ? 10 : 0xf, 0);
        func_ov107_020c0b90(*state, *(u16 *)(state + 0x14) == 1 ? 2 : 5, data_02041dc8, 0);
        func_ov258_020cfd3c(*(int *)(*state + 0x458), 0x7f8, 0xd48, 0);
        if (*(u16 *)(state + 0x14) != 0) {
            return;
        }
        func_ov258_020cfd3c(*(int *)(*state + 0x45c), 0x7f8, 0xd48, 0);
        return;
    }
    if (state[0xe] == 0 && func_ov258_020cd2cc(node) != 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    *(signed char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
