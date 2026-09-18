/* Attack end of the ov220 enemy: the +0x24 velocity copies the +0x30 heading, which then
 * shrinks to 0xb00 of itself. Once the +4 item is idle the actor plays animation 8 (looped),
 * publishes a zero vector with mode 2, the +0x14 timer becomes 0x4b000 scaled by 1.5 per +0x1c
 * phase, the +0x3e flag is cleared and the tick hands off to the guard tick. */
typedef unsigned char u8;
struct Vecx32 { int x, y, z; };

extern void func_01ffa724(int scale, void *v, void *d);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov107_020c0b90(int actor, int a, struct Vecx32 v, int b);
extern void func_0203c634(int *node, int slot, void *cb);
extern const struct Vecx32 data_02041dc8;
extern void func_ov220_020d3614(int *node);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov220_020d3510(int *node)
{
    int *state = (int *)node[1];
    int i;

    *(struct Vecx32 *)(state + 9) = *(struct Vecx32 *)(state + 0xc);
    func_01ffa724(0xb00, state + 0xc, state + 0xc);
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 8, 1);
    func_ov107_020c0b90(*state, 2, data_02041dc8, 0);
    state[5] = 0x4b000;
    for (i = 0; i < state[7]; i++) {
        state[5] = FX_Mul(state[5], 0x1800);
    }
    *(u8 *)((char *)state + 0x3e) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov220_020d3614);
}
