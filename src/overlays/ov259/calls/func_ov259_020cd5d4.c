/* Face the ov259 actor's +8 target: +0x7c becomes the heading of the flattened offset from the
 * actor's +0xb0 position to the target's +0x190 point. */
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern int func_020050b4(int x, int y);

void func_ov259_020cd5d4(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;

    if (state[2] == 0) {
        return;
    }
    VEC_Subtract((Vec3 *)(state[2] + 0x190), (Vec3 *)(*state + 0xb0), &d);
    func_01ff8d18(&d, &d);
    state[0x1f] = func_020050b4(d.x, d.z);
}
