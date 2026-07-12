/* Rotate the input vector by the actor's heading: read the fixed-point angle from
 * (*(param_2+4))+0x18, look up cos/sin in the shared trig table, build a Y-rotation
 * matrix, transform the vector in place and copy it to *out. */
extern void MTX_RotY33_(void *mtx, int cos, int sin);
extern void MTX_MultVec33(int *out, void *mtx, int *in);
extern const short data_0203d210[];
struct Mtx33_020cca74 { int m[9]; };
struct Vec3_020cca74 { int x, y, z; };
void func_ov231_020cca74(int *out, int param_2, int *vec) {
    struct Mtx33_020cca74 mtx;
    int v = *(int *)(*(int *)(param_2 + 4) + 0x18);
    int angle = (int)(((unsigned)(((long long)(int)(unsigned)v * 0x28be60db9391LL
                 + 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    MTX_RotY33_(&mtx, data_0203d210[angle * 2], data_0203d210[angle * 2 + 1]);
    MTX_MultVec33(vec, &mtx, vec);
    *(struct Vec3_020cca74 *)out = *(struct Vec3_020cca74 *)vec;
}
