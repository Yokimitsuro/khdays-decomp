extern void func_ov022_020ad44c(void *out, int self);
extern void func_ov022_02091324(int self, void *p);

typedef struct { int x, y, z; } Vec3;

typedef struct {
    Vec3 pos;
    short f0c, f0e, f10, f12;
    int f14, f18, f1c, f20, f24, f28;
} Params;

void func_ov092_020bb788(int self) {
    Params p;
    Vec3 v;
    func_ov022_020ad44c(&v, self);
    p.f10 = 0;
    p.f0e = 0;
    p.f0c = 0;
    p.pos = v;
    p.f14 = 2;
    p.f1c = 0;
    p.f20 = 0;
    p.f18 = 7;
    p.f24 = 0;
    p.f28 = 0;
    p.f12 = 0x1900;
    func_ov022_02091324(self, &p);
}
