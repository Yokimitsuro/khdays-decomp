/* Start of the ov258 marker effect: its rig transform resets, scales to 1.375 and moves to the
 * stored position, bit 1 of the rig's +0x5c flags clears, tracks 0 and 2 play and the brain waits on
 * 020d1618. */
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(void *transform);
extern void func_0203ca50(void *transform, int x, int y, int z);
extern void func_0203ca30(void *transform, const Vec3 *translation);
extern void func_0203b9fc(int rig, int channel, int a, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov258_020d1618(void);

void func_ov258_020d1564(int *node)
{
    int *state = (int *)node[1];

    func_0203c960((void *)(state[1] + 4));
    func_0203ca50((void *)(state[1] + 4), 0x1600, 0x1600, 0x1600);
    func_0203ca30((void *)(state[1] + 4), (Vec3 *)(state + 2));
    *(int *)(state[1] + 0x5c) &= ~2;
    func_0203b9fc(state[1], 0, 0, 0);
    func_0203b9fc(state[1], 2, 0, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov258_020d1618);
}
