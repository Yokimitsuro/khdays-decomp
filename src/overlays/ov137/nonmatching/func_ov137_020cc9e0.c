extern int VEC_Subtract();
extern int func_01ff8d18();
extern int FX_Inv();
extern int func_02023eb4();
extern int func_020050b4();

extern int data_02042258;
extern short data_0203d210[];

typedef struct { int x, y, z; } Vec3;

void func_ov137_020cc9e0(int *obj, Vec3 *out)
{
    int *v8;
    int *v0;
    int t;
    int s5;
    int s4;
    Vec3 local;

    v8 = (int *)obj[2];           /* obj->v8 at +8 */
    if (v8 == 0) {
        *out = *(Vec3 *)&data_02042258;
        return;
    }

    VEC_Subtract((char *)v8 + 0x74, (void *)obj[20], &local);  /* obj+0x50 */
    local.y = 0;
    t = func_01ff8d18(&local, &local);

    v8 = (int *)obj[2];
    v0 = (int *)obj[0];
    t = t - v8[32] - v0[32];     /* -[v8+0x80] -[v0+0x80] */
    t = FX_Inv(t, v0[182] < 0x1000 ? 0xf000 : v0[182]);  /* v0+0x2d8 */

    s5 = (t << 1) - 0x1000;
    if (s5 < -0x1000) s5 = -0x1000;
    if (s5 > 0x1000) s5 = 0x1000;

    s4 = (s5 < 0 ? -s5 : s5);
    s4 = 0x1000 - s4;
    {
        int a = s4 << 1;
        if (a < 0) a = -a;
        s4 = -s4 + func_02023eb4(a + 1);
    }

    s4 = (int)(((long long)s4 * 0x3244 + 0x800) >> 12);

    if (s5 > 0) {
        s4 = (func_020050b4(-local.x, -local.z) + 0x3244) - s4;
    } else {
        s4 = s4 + (func_020050b4(local.x, local.z) + 0x3244);
    }

    s4 = (int)(((long long)s4 * 0x28be60db9391LL + (0x800LL << 32)) >> 32);
    s4 = (int)((unsigned)(s4 << 4) >> 16) >> 4;

    out->x = data_0203d210[s4 * 2];
    out->y = 0;
    out->z = data_0203d210[s4 * 2 + 1];
}
