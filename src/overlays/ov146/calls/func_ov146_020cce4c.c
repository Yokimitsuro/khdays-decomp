/* Grab entry of the ov146 actor: the partner (+8) is grabbed (020ce2b4); both get bits 1 and 7 of their
 * +0x60 high byte and bit 0 of +0x1ae set, the partner's +0x3ac shape takes bit 1, the actor's bits 2-3
 * clear and its +0x3ac shape hides. A point 0.75 above the actor, turned by its +0xa0 rotation and
 * offset from the +0xc point, gets effect 0; sound 0/0x48 plays at the actor, +0x3c clears and the node
 * moves on to 020ccfe8. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;

extern int func_ov146_020ce2b4(int partner);
extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov146_020ccfe8(void);

void func_ov146_020cce4c(int *node)
{
    int *state = (int *)node[1];
    Vec3 at;

    func_ov146_020ce2b4(state[2]);
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x82) << 0x18) >> 0x10);
    }
    {
        u16 hw = *(u16 *)(state[2] + 0x60);
        *(u16 *)(state[2] + 0x60) = (hw & ~0xff00) |
            ((((((unsigned int)hw << 0x10) >> 0x18) | 0x82) << 0x18) >> 0x10);
    }
    *(u16 *)(*state + 0x1ae) |= 1;
    *(u16 *)(state[2] + 0x1ae) |= 1;
    ((B8 *)(*(int *)(state[2] + 0x3ac) + 8))->f |= 2;
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0xc) << 0x18) >> 0x10);
    }
    ((B8 *)(*(int *)(*state + 0x3ac) + 8))->f &= ~1;
    at.x = 0;
    at.y = 0xc00;
    at.z = 0;
    func_0202f384(&at, (void *)(*state + 0xa0), &at);
    VEC_Add(&at, (Vec3 *)state[3], &at);
    func_ov107_020c0b90(*state, 0, at, 0);
    func_ov107_020c5af8(*state, 0, 0x48, (void *)(*state + 0x74));
    state[0xf] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov146_020ccfe8);
}
