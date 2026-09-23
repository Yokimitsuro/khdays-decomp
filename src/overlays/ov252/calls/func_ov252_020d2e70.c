/* Start of an ov252 shard: its model's transform resets (0203c960) and moves to the spawner's +0x570
 * model point, bit 1 of the model's +0x5c flags clears, the spawner's +0x57a mask gains the shard's bit
 * (+0x24 index), layers 0, 2, 4 and 1 play (mode 0, 1), the rig pose resets, the +0x14 velocity is
 * scaled by 3.0, +0x20 clears and the node moves on to 020d2f6c. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(void *srt);
extern void func_0203ca30(void *srt, const Vec3 *v);
extern void func_0203b9fc(int rig, int channel, int a, int b);
extern void func_0203c7ac(int rig, int a);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d2f6c(void);

void func_ov252_020d2e70(int *node)
{
    int *state = (int *)node[1];

    func_0203c960((void *)(*state + 4));
    func_0203ca30((void *)(*state + 4), (Vec3 *)(*(int *)(state[1] + 0x570) + 0x14));
    *(int *)(*state + 0x5c) &= ~2;
    *(u16 *)(state[1] + 0x57a) |= 1 << *((signed char *)state + 0x24);
    func_0203b9fc(*state, 0, 0, 1);
    func_0203b9fc(*state, 2, 0, 1);
    func_0203b9fc(*state, 4, 0, 1);
    func_0203b9fc(*state, 1, 0, 1);
    func_0203c7ac(*state, 0);
    func_01ffa724(0x3000, (Vec3 *)(state + 5), (Vec3 *)(state + 5));
    state[8] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d2f6c);
}
