/* Re-acquires the current target (stored at +0x3dc of the owner), takes the vector to it,
 * records its horizontal angle at +0x34 and returns the flattened distance.  0 when there
 * is no target. */
typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern char *func_ov107_020cab14(char *o, int a);
extern void VEC_Subtract(Vec3 *a, Vec3 *b, Vec3 *out);
extern int func_020050b4(int a, int b);
extern int VEC_Mag(Vec3 *v);

int func_ov254_020cd128(char *self) {
    Vec3 d;
    char *ctx = *(char **)(self + 4);
    char *t;
    *(char **)(*(char **)ctx + 0x3dc) = func_ov107_020cab14(*(char **)ctx, 0);
    t = *(char **)(*(char **)ctx + 0x3dc);
    if (t == 0) {
        return 0;
    }
    VEC_Subtract((Vec3 *)(t + 0x190), *(Vec3 **)(ctx + 8), &d);
    *(int *)(ctx + 0x34) = func_020050b4(d.x, d.z);
    d.y = 0;
    return VEC_Mag(&d);
}
