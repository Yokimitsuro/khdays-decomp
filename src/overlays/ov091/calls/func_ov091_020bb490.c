typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } MtxFx33;
typedef struct {
    Vec3 pos;
    short sx, sy, sz, scale;
    int f14, f18, f1c, f20, f24, f28;
} Placement;

extern void MTX_RotY33_(MtxFx33 *, int, int);
extern void MTX_MultVec33(const Vec3 *, const MtxFx33 *, Vec3 *);
extern void VEC_Add(const Vec3 *, const Vec3 *, Vec3 *);
extern int VEC_Mag(const Vec3 *);
extern int func_01ff8d18(const Vec3 *, Vec3 *);
extern void func_ov022_02091324(char *, Placement *);
extern char *data_ov091_020bc240;
extern Vec3 data_ov091_020bc100;
extern short data_0203d210[];

void func_ov091_020bb490(char *self)
{
    Vec3 v;
    Vec3 temp;
    MtxFx33 mtx;
    Placement req;
    char *base = data_ov091_020bc240;
    char *block;
    char *state;
    unsigned short a;
    int i;

    block = base + 0xa4;
    state = block + 0x2c00;
    v = data_ov091_020bc100;
    temp = *(Vec3 *)(state + 0x124);
    a = (unsigned short)(*(unsigned short *)(*(char **)(self + 0x20) + 0x80) - 0x8000);
    i = a >> 4;
    MTX_RotY33_(&mtx, -data_0203d210[i * 2], -data_0203d210[i * 2 + 1]);
    temp.z += 0x99a;
    MTX_MultVec33(&temp, &mtx, &req.pos);
    VEC_Add(&req.pos, (Vec3 *)(self + 0x8c + 0x400), &req.pos);
    MTX_MultVec33(&v, &mtx, &v);
    if (VEC_Mag(&v) != 0)
        func_01ff8d18(&v, &v);
    req.sx = v.x;
    req.sy = v.y;
    req.sz = v.z;
    req.f14 = 1;
    req.f1c = 0;
    req.f20 = 0;
    req.f18 = 7;
    req.f24 = 0;
    req.f28 = 0;
    if (*(int *)(state + 8) != 2) {
        req.f24 = 0;
        req.scale = 0x2000;
    } else {
        req.f24 = 2;
        req.scale = 0x2580;
    }
    func_ov022_02091324(self, &req);
    if ((*(int *)self & 0x10000) == 0) {
        self[0x47a] = 3;
        self[0x47b] = 1;
    }
}
