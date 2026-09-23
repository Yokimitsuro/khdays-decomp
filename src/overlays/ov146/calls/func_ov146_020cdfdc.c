/* Hit entry of the ov146 actor: without a partner guard (+0x58) it plays effect 2 at the partner's
 * +0x74 point; bits 1, 2 and 6 of the +0x60 high byte and bit 0 of +0x1ae are set, the +0x3ac shape
 * hides, sound 0/0x49 plays at the actor, +0x3c clears and the node moves on to 020ce0bc. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov146_020ce0bc(void);

void func_ov146_020cdfdc(int *node)
{
    int *state = (int *)node[1];

    if (state[0x16] == 0) {
        func_ov107_020c0b90(*state, 2, *(Vec3 *)(state[2] + 0x74), 0);
    }
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x46) << 0x18) >> 0x10);
    }
    *(u16 *)(*state + 0x1ae) |= 1;
    ((B8 *)(*(int *)(*state + 0x3ac) + 8))->f &= ~1;
    func_ov107_020c5af8(*state, 0, 0x49, (void *)(*state + 0x74));
    state[0xf] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov146_020ce0bc);
}
