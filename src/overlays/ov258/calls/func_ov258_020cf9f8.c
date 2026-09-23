/* Wind-up tick of the ov258 actor: the +0x30 and +0x44 clocks run up at the frame rate; at 3.85 the
 * third step (+0x53 countdown 3) plays sound variant 0xc of the +0x58 bank at the +0x1c point, and
 * from 0x1298 the swing hit test runs (020cf6dc). Once the +4 rig is idle the +0x34 timer clears,
 * +0x50 = 1, pose 6 plays with effect 0x24 at the +0x1c point and the brain waits on 020cfb10. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 lo : 4; u8 hi : 4; } NibblePair;

extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_ov258_020cf6dc(int *node);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov258_020cfb10(void);

void func_ov258_020cf9f8(int *node)
{
    int *state = (int *)node[1];

    state[0xc] += *(int *)(node[0] + 0x2c);
    state[0x11] += *(int *)(node[0] + 0x2c);
    if (((NibblePair *)((u8 *)state + 0x53))->lo == 3 && state[0x11] >= 0x3da0) {
        ((NibblePair *)((u8 *)state + 0x53))->lo--;
        func_ov107_020c5af8(*state, *(short *)(state + 0x16), 0xc, state + 7);
    }
    if (state[0xc] >= 0x1298) {
        func_ov258_020cf6dc(node);
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    state[0xd] = 0;
    *(u16 *)(state + 0x14) = 1;
    func_ov107_020c9264(*state, 6, 0);
    func_ov107_020c0b90(*state, 0x24, *(Vec3 *)(state + 7), 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov258_020cfb10);
}
