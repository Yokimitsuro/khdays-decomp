/* Facing step of an ov260 part: when its +0x28 drift has a length the +0xa0 pose turns from the
 * rest axis to the drift direction; +0xf0 keeps the drift. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;

extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0203c9d0(char *srt, Quat *q);
extern const Vec3 data_02042258;

void func_ov260_020d1118(int *node)
{
    int *state = (int *)node[1];
    Quat q;
    Vec3 dir;

    if (func_01ff8d18((Vec3 *)(state + 10), &dir) != 0) {
        func_0202ed60(&q, &data_02042258, &dir);
        func_0203c9d0((char *)(*state + 0xa0), &q);
    }
    *(Vec3 *)(*state + 0xf0) = *(Vec3 *)(state + 10);
}
