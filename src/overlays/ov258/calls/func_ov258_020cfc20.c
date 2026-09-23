/* Swing tick of the ov258 actor: the +0x30 clock runs up at the frame rate and the swing hit test
 * (020cf6dc) runs until 0x330; a pending +0x50 flare (1) fires effect 0x25 at the +0x1c point. Once
 * the +4 rig is idle, without a +0x38 delay a follow-up (020cd2cc) may be picked, otherwise the next
 * move is 2. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_ov258_020cf6dc(int *node);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern int func_ov258_020cd2cc(int *node);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov258_020cfc20(int *node)
{
    int *state = (int *)node[1];

    state[0xc] += *(int *)(node[0] + 0x2c);
    if (state[0xc] < 0x330) {
        func_ov258_020cf6dc(node);
    }
    if (*(u16 *)(state + 0x14) == 1) {
        (*(u16 *)(state + 0x14))--;
        func_ov107_020c0b90(*state, 0x25, *(Vec3 *)(state + 7), 0);
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0xe] == 0 && func_ov258_020cd2cc(node) != 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    *(signed char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
