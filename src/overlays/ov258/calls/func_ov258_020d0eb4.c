/* Start of the ov258 beam effect: the beam rig's transform resets and moves to the stored start,
 * both rigs clear bit 1 of their +0x5c flags, the beam plays tracks 0, 2 and 3 and the glow rig loops
 * tracks 0 and 2, the beam is stretched 3.0 x 3.0 x 1.0 (glow 1.0) and posed; the +0x28 / +0x2c / +0x34
 * timers and the +0x48 flag clear and the brain waits on 020d0fe0. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(void *transform);
extern void func_0203ca30(void *transform, const Vec3 *translation);
extern void func_0203ca50(void *transform, int x, int y, int z);
extern void func_0203b9fc(int rig, int channel, int a, int b);
extern void func_0203c7ac(int rig, int a);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov258_020d0fe0(void);

void func_ov258_020d0eb4(int *node)
{
    int *state = (int *)node[1];

    func_0203c960((void *)(state[0] + 4));
    func_0203ca30((void *)(state[0] + 4), (Vec3 *)(state + 4));
    *(int *)(state[0] + 0x5c) &= ~2;
    func_0203b9fc(state[0], 0, 0, 0);
    func_0203b9fc(state[0], 2, 0, 0);
    func_0203b9fc(state[0], 3, 0, 0);
    *(int *)(state[1] + 0x5c) &= ~2;
    func_0203b9fc(state[1], 0, 0, 1);
    func_0203b9fc(state[1], 2, 0, 1);
    func_0203ca50((void *)(state[0] + 4), 0x3000, 0x3000, 0x1000);
    func_0203ca50((void *)(state[1] + 4), 0x1000, 0x1000, 0x1000);
    func_0203c7ac(state[0], 0);
    state[0xa] = 0;
    state[0xb] = 0;
    state[0xd] = 0;
    *(u8 *)(state + 0x12) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov258_020d0fe0);
}
