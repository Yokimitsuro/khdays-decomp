/* Jump entry: the actor's +0x390 latch is set, bits 1-3, 6 and 7 of its +0x60 high byte and bit 0
 * of +0x1ae are set, pose 0 plays and reaction 0x16d/9 fires at the +0x18 point; the +0x1c / +0x24
 * velocity is the +8 heading's forward direction times the 64-bit +0x28 speed, the +0x20 rise is
 * 0.75 and the node moves to 020d3890. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042258;
extern void func_ov254_020d3890(void);

void func_ov254_020d378c(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;

    *(int *)(*state + 0x390) = 1;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0xce) << 0x18) >> 0x10);
    }
    *(u16 *)(*state + 0x100 + 0xae) |= 1;
    func_ov107_020c9264(*state, 0, 0);
    func_ov107_020c5af8(*state, 0x16d, 9, (void *)state[6]);
    func_0202f384(&dir, state + 2, &data_02042258);
    state[7] = (int)((*(long long *)(state + 10) * dir.x + 0x80000000LL) >> 32);
    state[9] = (int)((*(long long *)(state + 10) * dir.z + 0x80000000LL) >> 32);
    state[8] = 0xc00;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020d3890);
}
