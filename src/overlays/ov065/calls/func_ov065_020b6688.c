/* Fires the ov046 enemy's ground shot (x4: ov046/065/084/101): aims at the target position when
 * one is within 0x9000, otherwise two units ahead along the heading; the point is dropped onto
 * the ground with a 0x7000 probe (resting 0x19a above a hit, or the full probe depth without one)
 * and a record request is built there: kind 7, the rig's pattern (+0x2d a4) as its tag, and a
 * speed of 0x1980 / 0x2200 / 0x2400 by pattern (pattern 2 also sets the homing flag). */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct {
    Vec3 pos;
    short f0c, f0e, f10, f12;
    int f14, f18, f1c, f20, f24, f28;
} Params;

extern int func_ov022_020ad114(char *self);
extern Vec3 *func_ov022_020ad0c0(char *self);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int VEC_Mag(const Vec3 *v);
extern void MTX_RotY33_(Mtx33 *m, int s, int c);
extern void MTX_MultVec33(const Vec3 *v, const Mtx33 *m, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern char *func_0202c268(unsigned int mask, Vec3 *from, Vec3 *dir, void *node);
extern void func_01ffd0e8(int t, const Vec3 *dir, const Vec3 *from, Vec3 *out);   /* Vec3ScaleAddQ27 */
extern void func_ov022_02091324(char *self, Params *p);
extern char *data_ov065_020b7340;
extern short data_0203d210[];

void func_ov065_020b6688(char *self)
{
    Params p;
    Vec3 pos;
    Vec3 origin;
    Vec3 down;
    Mtx33 m;
    Vec3 d;
    char *rig = data_ov065_020b7340 + 0x2c80;
    int bTarget = 0;
    u16 angle = *(u16 *)(*(char **)(self + 0x20) + 0x80) - 0x8000;
    char *hit;
    int idx;

    origin = *(Vec3 *)(self + 0x8c + 0x400);
    if (func_ov022_020ad114(self) != 0) {
        VEC_Subtract(func_ov022_020ad0c0(self), &origin, &d);
        if (VEC_Mag(&d) <= 0x9000) {
            pos = *func_ov022_020ad0c0(self);
            bTarget = 1;
        }
    }
    if (bTarget == 0) {
        idx = angle >> 4;
        MTX_RotY33_(&m, -data_0203d210[idx * 2], -data_0203d210[idx * 2 + 1]);
        pos.x = 0;
        pos.y = 0;
        pos.z = 0x2000;
        MTX_MultVec33(&pos, &m, &pos);
        VEC_Add(&origin, &pos, &pos);
    }
    down.x = 0;
    down.z = 0;
    down.y = -0x7000;
    hit = func_0202c268(*(u16 *)(self + 0x66), &pos, &down, *(void **)(self + 0x20));
    if (hit != 0) {
        func_01ffd0e8(*(int *)(hit + 0xc), &down, &pos, &pos);
        pos.y += 0x19a;
    } else {
        pos.y -= 0x7000;
    }
    p.f10 = 0;
    p.f0e = 0;
    p.f0c = 0;
    p.pos = pos;
    p.f14 = 0;
    p.f1c = 0;
    p.f20 = 0;
    p.f18 = 7;
    p.f24 = *(int *)(rig + 0x124);
    p.f28 = 0;
    switch (*(int *)(rig + 0x124)) {
    case 0:
        p.f12 = 0x1980;
        break;
    case 1:
        p.f12 = 0x2200;
        break;
    case 2:
        p.f12 = 0x2400;
        p.f28 = 1;
        break;
    }
    func_ov022_02091324(self, &p);
}
