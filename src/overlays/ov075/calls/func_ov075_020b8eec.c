/* Fires the ov036 enemy's spread (x4: ov036/054/074/091): the rig's pattern at +0x2da4 picks how
 * many shots go out and how far apart (0: one straight ahead; 1: two at half a turn; 2: three at
 * a third; 3/5: four at a quarter; 4: four at a quarter starting an eighth turn off). Each shot is
 * a record 1 request (kind 7, speed 0xe00) two units from the origin along its own heading. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct {
    Vec3 pos;
    short f0c, f0e, f10, f12;
    int f14, f18, f1c, f20, f24, f28;
} Params;

extern void MTX_RotY33_(Mtx33 *m, int s, int c);
extern void MTX_MultVec33(const Vec3 *v, const Mtx33 *m, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov022_02091324(char *self, Params *p);
extern short data_0203d210[];
extern char *data_ov075_020b9e20;

void func_ov075_020b8eec(char *self)
{
    Params p;
    Vec3 v;
    Vec3 origin;
    Mtx33 m;
    int angle = (u16)(*(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000);
    int count;
    int i;
    u16 a;
    int step;
    int idx;

    origin = *(Vec3 *)(self + 0x8c + 0x400);
    switch (*(int *)(data_ov075_020b9e20 + 0x2da4)) {
    case 0:
        a = angle;
        count = 1;
        step = 0;
        break;
    case 1:
        a = angle;
        count = 2;
        step = 0x7fff;
        break;
    case 2:
        a = angle;
        count = 3;
        step = 0x5555;
        break;
    case 3:
        a = angle;
        count = 4;
        step = 0x3fff;
        break;
    case 4:
        a = angle + 0x1fff;
        count = 4;
        step = 0x3fff;
        break;
    case 5:
        a = angle;
        count = 4;
        step = 0x3fff;
        break;
    }
    for (i = 0; i < count; i++) {
        p.f0c = p.f0e = p.f10 = 0;
        v.x = 0;
        v.y = 0;
        v.z = 0x2000;
        idx = a >> 4;
        MTX_RotY33_(&m, -data_0203d210[idx * 2], -data_0203d210[idx * 2 + 1]);
        MTX_MultVec33(&v, &m, &v);
        VEC_Add(&origin, &v, &p.pos);
        p.f14 = 1;
        p.f1c = 0;
        p.f20 = 0;
        p.f18 = 7;
        p.f24 = 0;
        p.f28 = 0;
        p.f12 = 0xe00;
        func_ov022_02091324(self, &p);
        a = a + step;
    }
}
