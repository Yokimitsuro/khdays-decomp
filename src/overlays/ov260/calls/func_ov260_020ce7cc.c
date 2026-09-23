/* Slam entry of the ov260 actor: bit 6 of the +0x60 high byte is set, pose 0xd plays, its +0x428
 * part takes motion 5, effects 9 and 0x20 start at the +0x10 point, the actor is knocked back at its
 * feet (+0x74 lowered by the +0x13c height, mode 4), +0x74 clears and the node moves on to 020ce8b0. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov260_020cd148(int owner, int mode, int arg);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020ce8b0(void);

void func_ov260_020ce7cc(int *node)
{
    int *state = (int *)node[1];
    Vec3 at;

    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x40) << 0x18) >> 0x10);
    }
    func_ov107_020c9264(*state, 0xd, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x428), 5, 0);
    func_ov260_020cd148(*state, 9, state[4]);
    func_ov260_020cd148(*state, 0x20, state[4]);
    {
        int actor = *state;

        at = *(Vec3 *)(actor + 0x74);
        at.y -= *(int *)(actor + 0x13c);
        func_ov107_020c0b90(actor, 4, at, 0);
    }
    state[0x1d] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020ce8b0);
}
