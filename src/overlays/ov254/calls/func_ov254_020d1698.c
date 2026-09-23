/* Move entry: bit 2 of the actor's +0x60 high byte is set, pose 0 plays (looping), the next
 * waypoint is chosen into +0x34 (020cd5f4) and copied to +0x30, the first tick runs at once and
 * the node moves to 020d1710. */
typedef unsigned short u16;

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov254_020cd5f4(int *state, int a, int *out);
extern void func_ov254_020d1710(int *node);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov254_020d1698(int *node)
{
    int *state = (int *)node[1];

    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 4) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*state, 0, 1);
    func_ov254_020cd5f4(state, 0, state + 0xd);
    state[0xc] = state[0xd];
    func_ov254_020d1710(node);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov254_020d1710);
}
