typedef struct { int x; int y; int z; } Vec3;

extern void VEC_Subtract(Vec3 *a, Vec3 *b, Vec3 *out);
extern void func_02033ef8(Vec3 *dst, Vec3 *a, Vec3 *b);

typedef struct {
    char _00[4];
    char part0[0x48];
    char part1[0xac];
    int selector;
} Obj02020e20;

void func_02020e20(Obj02020e20 *obj)
{
    char *base;
    Vec3 tmp;

    if (obj->selector == 1) {
        base = obj->part1;
    } else {
        base = obj->part0;
    }

    VEC_Subtract((Vec3 *)(base + 0x14), (Vec3 *)(base + 0x20), &tmp);
    func_02033ef8((Vec3 *)(base + 0x20), &tmp, (Vec3 *)(base + 0x2c));
}
