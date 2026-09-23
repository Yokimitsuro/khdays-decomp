/* Start of an ov252 gem: its model's transform resets (0203c960) and moves to the gem's +8 point, bit 1
 * of the model's +0x5c flags clears, the owner's +0x57e mask gains the gem's bit (+0x24 index), layers
 * 0, 2, 4 and 1 play (mode 0, 0), the model is scaled 2.5/4.06 (big gem, +0x25) or 2.0/3.25, the rig pose
 * resets, +0x20 clears, the first-blink flag (+0x26) is set and the node moves on to 020d3d10. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(void *srt);
extern void func_0203ca30(void *srt, const Vec3 *v);
extern void func_0203b9fc(int rig, int channel, int a, int b);
extern void func_0203ca50(void *placement, int x, int y, int z);
extern void func_0203c7ac(int rig, int a);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d3d10(void);

void func_ov252_020d3bdc(int *node)
{
    int *state = (int *)node[1];

    func_0203c960((void *)(*state + 4));
    func_0203ca30((void *)(*state + 4), (Vec3 *)(state + 2));
    *(int *)(*state + 0x5c) &= ~2;
    *(u16 *)(state[1] + 0x57e) |= 1 << *((signed char *)state + 0x24);
    func_0203b9fc(*state, 0, 0, 0);
    func_0203b9fc(*state, 2, 0, 0);
    func_0203b9fc(*state, 4, 0, 0);
    func_0203b9fc(*state, 1, 0, 0);
    if (*((unsigned char *)state + 0x25) == 0) {
        state[5] = 0x2000;
        state[6] = 0x3400;
        state[7] = 0x2000;
    } else {
        state[5] = 0x2800;
        state[6] = 0x4100;
        state[7] = 0x2800;
    }
    func_0203ca50((void *)(*state + 4), state[5], state[6], state[7]);
    func_0203c7ac(*state, 0);
    state[8] = 0;
    *((unsigned char *)state + 0x26) = 1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d3d10);
}
