/* Collapse entry of the ov238 actor: bit 7 of the +0x60 high byte is set, the +0x388 shape hides, its
 * +0x398 partner plays effect 2 at the +8 point, sound 0x12e/9 plays there, the +0x2c/+0x1c/+0x20
 * timers clear and the node moves on to 020d3184. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov238_020d3184(void);

void func_ov238_020d30b8(int *node)
{
    int *state = (int *)node[1];

    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x80) << 0x18) >> 0x10);
    }
    ((B8 *)(*(int *)(*state + 0x388) + 8))->f &= ~1;
    func_ov107_020c0b90(*(int *)(*state + 0x398), 2, *(Vec3 *)state[2], 0);
    func_ov107_020c5af8(*state, 0x12e, 9, (void *)state[2]);
    state[0xb] = 0;
    state[7] = 0;
    state[8] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov238_020d3184);
}
