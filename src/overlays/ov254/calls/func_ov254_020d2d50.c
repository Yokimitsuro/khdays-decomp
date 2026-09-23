/* Plan a jump from the +0x18 point to `target`: starting 0.75 up with a rising step of 0.75 that
 * shrinks by 0xd0 per frame, count the frames until the arc falls back to the target's height;
 * the +0x28 horizontal speed is the flat distance over that count (64-bit, 20 fraction bits), the +8 heading faces
 * the target, +0x48 is set and the next move is 2. */
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern long long func_020201b8(long long num, long long den);
extern void func_0202ed60(void *rotation, const Vec3 *from, const Vec3 *to);
extern const Vec3 data_02042258;

void func_ov254_020d2d50(int *state, Vec3 *target)
{
    Vec3 p;
    Vec3 d;
    int step;
    int n;

    p = *(Vec3 *)state[6];
    p.y += 0xc00;
    step = 0xc00;
    n = 1;
    while (step > 0 || p.y > target->y) {
        step -= 0xd0;
        p.y += step;
        n++;
    }
    VEC_Subtract(target, (Vec3 *)state[6], &d);
    d.y = 0;
    *(long long *)(state + 10) = func_01ff8d18(&d, &d);
    *(long long *)(state + 10) = func_020201b8(*(long long *)(state + 10) << 20, n);
    func_0202ed60(state + 2, &data_02042258, &d);
    state[0x12] = 1;
    *(signed char *)(*state + 0x1c7) = 2;
}
