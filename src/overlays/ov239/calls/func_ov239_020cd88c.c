/* Guard-break entry of the ov239 enemy: drops bit 0 of the +0x60 high byte, sets bits 0-1 of
 * +0x1ae and bits 1/2/7 of the high byte, clears bit 0 of the +0x38c part's +8 word, spawns
 * effect 1 at the +8 point, fires reaction 0x138 mode 0xa at the actor's position and hands off
 * to cd980. */
typedef struct { int x, y, z; } VecFx32;
struct hw60 { unsigned short lo : 8, hi : 8; };
struct LowByte32 { unsigned bits : 8; };

extern void func_ov107_020c0b90(int actor, int a, VecFx32 v, int d);
extern void func_ov107_020c5af8(int actor, int a, int b, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov239_020cd980(int *node);

void func_ov239_020cd88c(int *node)
{
    int *state = (int *)node[1];
    unsigned short *hw;
    unsigned int h;

    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    *(unsigned short *)(*state + 0x1ae) |= 3;
    hw = (unsigned short *)(*state + 0x60);
    h = *hw;
    *hw = h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10);
    ((struct LowByte32 *)(*(int *)(*state + 0x38c) + 8))->bits &= ~1;
    func_ov107_020c0b90(*state, 1, *(VecFx32 *)state[2], 0);
    func_ov107_020c5af8(*state, 0x138, 0xa, (void *)(*state + 0x74));
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov239_020cd980);
}
