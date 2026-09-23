/* Start of an ov252 gem shot: its model's transform resets and moves to the spawner's +0x570 model
 * point at scale 4.0, bit 1 of its +0x5c flags clears, the spawner's +0x57c mask gains its bit (+0x34
 * index), layers 0, 2, 4 and 1 play (mode 0, 0) and the rig pose resets. With no target (020cab14, into
 * +8) the layers fade out (mode 2) and the node moves on to 020d38e8; otherwise the spawner plays effect
 * 5 at the origin, a target below 10.0 sets +0x38, the +0x18 heading (and its +0x24 copy) points from
 * the +0xc point to the target, +0x30 clears and the node moves on to 020d346c. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(void *srt);
extern void func_0203ca30(void *srt, const Vec3 *v);
extern void func_0203ca50(void *placement, int x, int y, int z);
extern void func_0203b9fc(int rig, int channel, int a, int b);
extern void func_0203c7ac(int rig, int a);
extern int func_ov107_020cab14(int actor, int *distOut);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d38e8(void);
extern void func_ov252_020d346c(void);
extern const Vec3 data_02041dc8;

void func_ov252_020d326c(int *node)
{
    int *state = (int *)node[1];

    func_0203c960((void *)(*state + 4));
    func_0203ca30((void *)(*state + 4), (Vec3 *)(*(int *)(state[1] + 0x570) + 0x14));
    func_0203ca50((void *)(*state + 4), 0x4000, 0x4000, 0x4000);
    *(int *)(*state + 0x5c) &= ~2;
    *(u16 *)(state[1] + 0x57c) |= 1 << *((signed char *)state + 0x34);
    func_0203b9fc(*state, 0, 0, 0);
    func_0203b9fc(*state, 2, 0, 0);
    func_0203b9fc(*state, 4, 0, 0);
    func_0203b9fc(*state, 1, 0, 0);
    func_0203c7ac(*state, 0);
    state[2] = func_ov107_020cab14(state[1], 0);
    if (state[2] == 0) {
        func_0203b9fc(*state, 0, 2, 0);
        func_0203b9fc(*state, 2, 2, 0);
        func_0203b9fc(*state, 4, 2, 0);
        func_0203b9fc(*state, 1, 2, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d38e8);
    } else {
        func_ov107_020c0b90(state[1], 5, data_02041dc8, 0);
        if (*(int *)(state[2] + 0x194) < 0xa000) {
            state[0xe] = 1;
        }
        VEC_Subtract((Vec3 *)(state[2] + 0x190), (Vec3 *)(state + 3), (Vec3 *)(state + 6));
        func_01ff8d18((Vec3 *)(state + 6), (Vec3 *)(state + 6));
        *(Vec3 *)(state + 9) = *(Vec3 *)(state + 6);
        state[0xc] = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d346c);
    }
}
