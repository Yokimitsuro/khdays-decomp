/* Leap tick of the ov258 actor: the +0x44 clock runs up at the frame rate with step cues (020cd6c8)
 * at 1 x 0x88 (variant 0xb) and 0x1c x 0x88 (variant 0x1b with a +0x460 partner, else 0x16); once the
 * +4 rig is idle pose 8 plays with effect 0x22 at the +0x1c point, the +0x30 timer clears and the
 * brain waits on 020cf894. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_ov258_020cd6c8(int *node, int step, int phase, u16 variant);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov258_020cf894(void);

void func_ov258_020cf7c8(int *node)
{
    int *state = (int *)node[1];

    state[0x11] += *(int *)(node[0] + 0x2c);
    func_ov258_020cd6c8(node, 1, 5, 0xb);
    func_ov258_020cd6c8(node, 0x1c, 4, *(int *)(*state + 0x460) != 0 ? 0x1b : 0x16);
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 8, 0);
    func_ov107_020c0b90(*state, 0x22, *(Vec3 *)(state + 7), 0);
    state[0xc] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov258_020cf894);
}
