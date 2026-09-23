/* Burst entry of the ov260 actor: it is knocked back at its own +0x74 position (mode 3), effect 0xc
 * starts there, bits 1 and 7 of the +0x60 high byte are set, +0x70 clears and the node moves on to
 * 020cf518. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov260_020cd148(int owner, int mode, int arg);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov260_020cf518(void);

void func_ov260_020cf484(int *node)
{
    int *state = (int *)node[1];

    func_ov107_020c0b90(*state, 3, *(Vec3 *)(*state + 0x74), 0);
    func_ov260_020cd148(*state, 0xc, *state + 0x74);
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x82) << 0x18) >> 0x10);
    }
    state[0x1c] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov260_020cf518);
}
