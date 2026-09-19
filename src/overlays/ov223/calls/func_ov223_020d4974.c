/* Charge pose tick of the ov223 enemy: the +0x14 velocity is copied to the owner's +0xf0 and,
 * in variants 0 and 1, the owner's +0xa0 pose is scaled by 2.0 x +0x40 (y by the inverse of
 * 0x733 over 1.0) and set to face the +0x20 target from data_02042240 (ed60). */
typedef struct { int x, y, z; } Vec3;
typedef struct { int q[4]; } Quat;

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

extern int FX_Inv(int num, int den);
extern void func_0203ca50(void *pose, int x, int y, int z);
extern void func_0202ed60(Quat *out, const Vec3 *from, const Vec3 *to);
extern void func_0203c9d0(void *pose, Quat *q);
extern const Vec3 data_02042240;

void func_ov223_020d4974(int *node)
{
    int *state = (int *)node[1];
    Quat q;
    int nScale;
    char *owner;

    *(Vec3 *)(*state + 0xf0) = *(Vec3 *)(state + 5);
    if (state[0x12] != 0 && state[0x12] != 1) {
        return;
    }
    nScale = FX_MUL(state[0x10], 0x2000);
    owner = (char *)*state;
    func_0203ca50(owner + 0xa0, nScale, FX_Inv(0x10000, 0x733), nScale);
    func_0202ed60(&q, &data_02042240, (Vec3 *)(state + 8));
    func_0203c9d0((void *)(*state + 0xa0), &q);
}
