/* Attack entry of the ov299 enemy: raises the +0x38c flag and bit 7 of the +0x60 high byte,
 * deactivates the +0x388 shape, aims effect 0 at the +4 target position and fires reaction
 * 0x170/4 there; the +0x24 timer and the +0xc velocity are cleared before handing off to the
 * d45d4 tick. */
typedef struct { int x, y, z; } VecFx32;

extern void func_ov107_020c0b90(int actor, int a, VecFx32 v, int d);
extern void func_ov107_020c5af8(int actor, int id, int mode, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov299_020d45d4(int *node);
extern const VecFx32 data_02041dc8;

struct LowByte32 { unsigned bits : 8; };

void func_ov299_020d44fc(int *node)
{
    int *state = (int *)node[1];

    *(int *)(*state + 0x38c) = 1;
    {
        unsigned short hw60 = *(unsigned short *)(*state + 0x60);
        *(unsigned short *)(*state + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10);
    }
    ((struct LowByte32 *)(*(int *)(*state + 0x388) + 8))->bits &= ~1;
    func_ov107_020c0b90(*state, 0, *(VecFx32 *)state[1], 0);
    func_ov107_020c5af8(*state, 0x170, 4, (void *)state[1]);
    state[9] = 0;
    *(VecFx32 *)(state + 3) = data_02041dc8;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov299_020d45d4);
}
