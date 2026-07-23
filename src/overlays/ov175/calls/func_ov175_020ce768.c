/* Launch the lunge: fire event 0x142 on the sub-object, clear the travel accumulator, set bit 0
 * of the hw60 high byte and drop 0x8c from it, raise bit 0 of the status word at +8 of the
 * component at +0x388, copy the aim vector from the object's +0x390 into state[5..7] and scale it
 * by 0x600 into the velocity slot at state[2..4].
 *
 * Matched byte-exact 2026-07-23, first compile. One of three byte-identical siblings. */
typedef struct { int x, y, z; } VecFx32;

extern void func_ov107_020c5af8(int obj, int a, int b, int c);
extern void func_01ffa724(int scale, void *in, void *out);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov175_020ce844(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct LowByte32 { unsigned bits : 8; };

void func_ov175_020ce768(int *node) {
    int *state = (int *)node[1];

    func_ov107_020c5af8(state[0], 0x142, 5, state[1]);
    state[8] = 0;
    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 1) << 0x18) >> 0x10);
    }
    ((struct hw60 *)(state[0] + 0x60))->hi &= ~0x8c;
    ((struct LowByte32 *)(*(int *)(state[0] + 0x388) + 8))->bits |= 1;
    *(VecFx32 *)(state + 5) = *(VecFx32 *)(state[0] + 0x390);
    func_01ffa724(0x600, state + 5, state + 2);
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov175_020ce844);
}
