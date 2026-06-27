typedef long fx32;
typedef struct { fx32 x, y, z; } VecFx32;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_01ffd0e8(int a, void *b, void *c, void *d);
extern void func_01ffcfd0(VecFx32 *a, void *b);
extern int  VEC_DotProductFx16(VecFx32 *a, void *b);

void func_020294b0(char *a, char *b, char *c) {
    VecFx32 tmp;
    VecFx32 diff;

    func_01ffd0e8(*(int *)(b + 0x78), b + 0x1c, b + 0x10, &tmp);
    VEC_Subtract(&tmp, (const VecFx32 *)(a + 0x2c), &diff);
    diff.y = 0;
    func_01ffcfd0(&diff, c + 0x14);
    *(int *)(c + 0x1c) = VEC_DotProductFx16(&tmp, c + 0x14);
    *(int *)(c + 0x80) = *(int *)(a + 0x24);
}
