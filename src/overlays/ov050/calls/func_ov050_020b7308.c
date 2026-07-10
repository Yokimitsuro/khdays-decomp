struct vec3 { int x, y, z; };

extern void VEC_Add(struct vec3 *dst, struct vec3 *a, struct vec3 *b);
extern void VEC_Subtract(struct vec3 *a, struct vec3 *b, struct vec3 *out);
extern void func_01ff8d18(struct vec3 *dst, struct vec3 *src);
extern void MTX_RotY33_(int *mtx, int a, int b);
extern void MTX_MultVec33(struct vec3 *a, int *mtx, struct vec3 *out);
extern int FX_Inv(int a, int b);
extern void func_01ffa724(int scale, struct vec3 *src, struct vec3 *dst);
extern void VEC_MultAdd(int t, struct vec3 *a, struct vec3 *b, struct vec3 *out);
extern int func_02023c40(void);

/* Approach-solver: advance the approach timer (+4 += param_4), take the target
 * offset, blend the current facing toward it with a rotation-limited step whose
 * magnitude eases in over the first 0x6000 of the timer, then scale by the entity's
 * base speed (1.5x in the alt mode) and write the resulting velocity to param_1. */
void func_ov050_020b7308(struct vec3 *param_1, int param_2, int param_3, int param_4) {
    struct { int mtx[9]; struct vec3 v24; struct vec3 v30; struct vec3 v3c; } f;
    int *iVar1 = *(int **)(param_3 + 0x138);
    int t;

    *(int *)(param_3 + 4) += param_4;
    f.v3c = *(struct vec3 *)(param_3 + 0xcc);
    VEC_Add(&f.v3c, (struct vec3 *)(param_3 + 0x1c), &f.v3c);
    VEC_Subtract(&f.v3c, (struct vec3 *)(param_3 + 0x10), &f.v24);
    func_01ff8d18(&f.v24, &f.v24);
    MTX_RotY33_(f.mtx, 0x1000, 0);
    MTX_MultVec33(&f.v24, f.mtx, &f.v30);
    if (*(int *)(param_3 + 4) < 0x6000) {
        int r = FX_Inv((*(int *)(param_3 + 4) / 3) * 3, 0x6000);
        t = (r / 8) + 0x1000;
    } else {
        t = 0x1000;
    }
    func_01ffa724(t, &f.v30, &f.v30);
    VEC_MultAdd(0x1000 - t, &f.v24, &f.v30, &f.v24);
    func_01ff8d18(&f.v24, &f.v24);
    {
        int mode = func_02023c40();
        int sc;
        if (mode == 1) {
            sc = (iVar1[4] * 3) / 2;
        } else {
            sc = iVar1[4];
        }
        func_01ffa724(sc, &f.v24, &f.v24);
    }
    *param_1 = f.v24;
}
