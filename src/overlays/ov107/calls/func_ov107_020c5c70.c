typedef int fx32;

static inline fx32 FX_Mul(fx32 a, fx32 b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern int FX_Inv(int a, int b);

typedef struct {
    char pad[0x370];
    short s70;
    short s72;
    short s74;
    short s76;
    short s78;
} Obj;

int func_ov107_020c5c70(Obj *obj, fx32 p1, fx32 p2)
{
    fx32 sum = FX_Mul(obj->s74, p2) - FX_Mul(obj->s72, p1) + (obj->s70 << 12);
    if (sum < 0x1000) sum = 0x1000;
    return FX_Inv(FX_Mul(obj->s76, p1) + (obj->s78 << 12), sum);
}
