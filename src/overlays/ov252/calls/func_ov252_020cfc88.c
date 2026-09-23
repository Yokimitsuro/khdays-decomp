/* Whether the ov252 actor's +8 point is at least 4.0 from the origin on the ground plane. */
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern const Vec3 data_02041dc8;

int func_ov252_020cfc88(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    Vec3 p;

    p = *(Vec3 *)state[2];
    p.y = 0;
    VEC_Subtract(&data_02041dc8, &p, &d);
    return func_01ff8d18(&d, &d) >= 0x40000;
}
