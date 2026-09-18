/* func_ov245_020d2bc4 -- plan a hop towards the target: from the state's +8 origin raises the
 * landing height by `step` per hop (each hop 0.75 shorter) while the step is still rising or the
 * landing height stays above the target's +4 height, aims the +0x18 direction at the target (normalised, its length kept at +0x30 as a
 * 64-bit value) and divides that length by the number of hops (64-bit divide). */
typedef struct { int x, y, z; } Vec3;
typedef long long s64;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern s64 func_020201b8(s64 num, s64 den);

void func_ov245_020d2bc4(int *state, Vec3 *target, int step) {
    Vec3 goal;
    int hops;

    goal = *(Vec3 *)state[2];
    goal.y += step;
    hops = 1;
    while (step > 0 || goal.y > target->y) {
        step -= 0xc0;
        goal.y += step;
        hops++;
    }
    VEC_Subtract(target, (Vec3 *)state[2], (Vec3 *)(state + 6));
    *(s64 *)(state + 0xc) = func_01ff8d18((Vec3 *)(state + 6), (Vec3 *)(state + 6));
    *(s64 *)(state + 0xc) = func_020201b8(*(s64 *)(state + 0xc) << 20, hops);
}
