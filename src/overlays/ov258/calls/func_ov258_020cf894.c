/* Hover tick of the ov258 actor: the +0x30 and +0x44 clocks run up at the frame rate; at 3.85 the
 * third step (+0x53 countdown 3) plays sound variant 0xc of the +0x58 bank at the +0x1c point. Each
 * time the +4 rig finishes: after 1.0 pose 9 plays with the wind-up sound (variant 0x1b with a +0x460
 * partner, else 0x17) at the +0x430 rig, the +0x30 clock clears, effect 0x23 plays and the brain
 * waits on 020cf9f8; before that pose 8 replays with effect 0x22. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 lo : 4; u8 hi : 4; } NibblePair;

extern void func_ov107_020c5af8(int actor, int bank, u16 variant, int at);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov258_020cf9f8(void);

void func_ov258_020cf894(int *node)
{
    int *state = (int *)node[1];

    state[0xc] += *(int *)(node[0] + 0x2c);
    state[0x11] += *(int *)(node[0] + 0x2c);
    if (((NibblePair *)((u8 *)state + 0x53))->lo == 3 && state[0x11] >= 0x3da0) {
        ((NibblePair *)((u8 *)state + 0x53))->lo--;
        func_ov107_020c5af8(*state, *(short *)(state + 0x16), 0xc, (int)(state + 7));
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0xc] >= 0x1000) {
        func_ov107_020c9264(*state, 9, 0);
        func_ov107_020c5af8(*state, *(short *)(state + 0x16), *(int *)(*state + 0x460) != 0 ? 0x1b : 0x17,
                            *(int *)(*state + 0x430) + 0x14);
        state[0xc] = 0;
        func_ov107_020c0b90(*state, 0x23, *(Vec3 *)(state + 7), 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov258_020cf9f8);
        return;
    }
    func_ov107_020c9264(*state, 8, 0);
    func_ov107_020c0b90(*state, 0x22, *(Vec3 *)(state + 7), 0);
}
