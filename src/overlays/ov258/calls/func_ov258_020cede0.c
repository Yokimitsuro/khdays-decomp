/* Aim marker of the ov258 actor: the flat direction from the +0xc point to a spot past the `side`
 * hand (+0x44c / +0x450) along the alternating +0x3f8 offset (+0x3c parity, 5.0 plus the +0x40 gap)
 * is normalised; within 5.0 a d100 roll under 50 marks the target's +0x190 point instead. Effect 0x1b
 * plays at that spot 15.6 high. */
typedef struct { int x, y, z; } Vec3;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_02023eb4(int bound);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);

void func_ov258_020cede0(int *node, int side)
{
    int *state = (int *)node[1];
    Vec3 from;
    Vec3 dir;
    Vec3 at;

    from = *(Vec3 *)state[3];
    func_01ffa724(state[0x10] + 0x5000, &((Vec3 *)(*state + 0x3f8))[state[0xf] % 2], &at);
    VEC_Add((Vec3 *)((side == 0 ? *(int *)(*state + 0x44c) : *(int *)(*state + 0x450)) + 0x14), &at, &at);
    from.y = 0;
    at.y = 0;
    VEC_Subtract(&at, &from, &dir);
    func_01ff8d18(&dir, &dir);
    if (state[0x10] < 0x5000 && (unsigned int)func_02023eb4(100) < 0x32) {
        at = *(Vec3 *)(*(int *)(*state + 0x454) + 0x190);
    }
    at.y = 0xfa00;
    func_ov107_020c0b90(*state, 0x1b, at, 0);
}
