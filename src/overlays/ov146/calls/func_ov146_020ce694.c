/* Launch the ov146 actor along `dir`: the +0xc velocity is its unit vector at 0.5 with a 0.625 lift,
 * +0x1c clears and the next move is 1. */
typedef struct { int x, y, z; } Vec3;

extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);

void func_ov146_020ce694(int *state, Vec3 dir)
{
    func_01ff8d18(&dir, (Vec3 *)(state + 3));
    func_01ffa724(0x800, (Vec3 *)(state + 3), (Vec3 *)(state + 3));
    state[4] = 0xa00;
    state[7] = 0;
    *(unsigned char *)(*state + 0x1c7) = 1;
}
