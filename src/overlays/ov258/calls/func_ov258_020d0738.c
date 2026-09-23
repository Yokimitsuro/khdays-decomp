/* Start of the ov258 shot effect: its rig transform resets, scales to 0.5 and moves to the stored
 * position, bit 1 of the rig's +0x5c flags clears, tracks 0 and 2 play and the rig is posed; the
 * +0x14 timer and +0x18 flag clear, +0x19 is set and the brain waits on 020d0800. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(void *transform);
extern void func_0203ca50(void *transform, int x, int y, int z);
extern void func_0203ca30(void *transform, const Vec3 *translation);
extern void func_0203b9fc(int rig, int channel, int a, int b);
extern void func_0203c7ac(int rig, int a);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov258_020d0800(void);

void func_ov258_020d0738(int *node)
{
    int *state = (int *)node[1];

    func_0203c960((void *)(*state + 4));
    func_0203ca50((void *)(*state + 4), 0x800, 0x800, 0x800);
    func_0203ca30((void *)(*state + 4), (Vec3 *)(state + 2));
    *(int *)(*state + 0x5c) &= ~2;
    func_0203b9fc(*state, 0, 0, 0);
    func_0203b9fc(*state, 2, 0, 0);
    func_0203c7ac(*state, 0);
    state[5] = 0;
    *(u8 *)(state + 6) = 0;
    *((u8 *)state + 0x19) = 1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov258_020d0800);
}
