extern void func_ov022_02091324(int self, void *p);

typedef struct { int x, y, z; } Vec3;

typedef struct {
    Vec3 vec;
    short f0c, f0e, f10, f12;
    int f14, f18, f1c, f20, f24, f28;
} Params;

void func_ov087_020b915c(int self, int *ctx, Vec3 *src) {
    Params p;
    p.vec = *src;
    p.f14 = 0;
    p.f1c = 1;
    p.f20 = 0;
    p.f0c = 0;
    p.f0e = 0x1000;
    p.f10 = 0;
    p.f28 = 0;
    p.f24 = 0;
    p.f18 = 0;
    p.f12 = 0x2100;
    if (ctx[0x46] != 0) {
        p.f28 = 1;
        p.f24 = 1;
        p.f12 = 0x2480;
        p.f18 = 1;
    }
    func_ov022_02091324(self, &p);
}
