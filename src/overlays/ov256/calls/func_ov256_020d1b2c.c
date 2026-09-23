/* Heading from an ov256 helper's orbit point (+0xc anchor plus the +0x10 offset) toward its +0x34
 * target, as a flat angle. */
typedef struct { int x, y, z; } Vec3;

extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int y);

int func_ov256_020d1b2c(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    Vec3 p;

    p = *(Vec3 *)state[3];
    VEC_Add(&p, (Vec3 *)(state + 4), &p);
    VEC_Subtract(&p, (Vec3 *)(state + 0xd), &d);
    return func_020050b4(d.x, d.z);
}
