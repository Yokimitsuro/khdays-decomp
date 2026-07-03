extern int data_ov050_020b75c0;
extern short data_0203d210[];

struct v3 { int x, y, z; };

struct spawn_desc {
    struct v3 vec;   /* 0x00 */
    short sx;        /* 0x0c */
    short sy;        /* 0x0e */
    short sz;        /* 0x10 */
    short flag;      /* 0x12 */
    int f14;         /* 0x14 */
    int f18;         /* 0x18 */
    int f1c;         /* 0x1c */
    int f20;         /* 0x20 */
    int f24;         /* 0x24 */
    int f28;         /* 0x28 */
};

struct frame {
    struct v3 buf0;             /* 0x00 */
    int mtx[9];                 /* 0x0c */
    struct spawn_desc desc;     /* 0x30 */
};

extern void MTX_RotY33_(int *mtx, int cos, int sin);
extern void MTX_MultVec33(struct v3 *dst, int *mtx, struct v3 *src);
extern int VEC_Mag(struct v3 *v);
extern void func_01ff8d18(struct v3 *dst, struct v3 *src);
extern void func_ov022_02091324(int global, void *desc);

void func_ov050_020b7208(int this, int param2) {
    struct frame f;
    int global = data_ov050_020b75c0;
    int i;
    int angle = 0;

    f.desc.vec = *(struct v3 *)this;
    f.desc.f14 = 2;
    f.desc.f1c = 0;
    f.desc.f20 = 0;
    f.desc.f18 = 7;
    f.desc.f24 = 0;
    f.desc.f28 = 0;
    f.desc.flag = 0x1c00;

    for (i = 0; i < 3; i++) {
        int idx = angle >> 4;
        f.buf0 = *(struct v3 *)param2;
        MTX_RotY33_(f.mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
        MTX_MultVec33(&f.buf0, f.mtx, &f.buf0);
        if (VEC_Mag(&f.buf0) != 0) {
            func_01ff8d18(&f.buf0, &f.buf0);
        }
        f.desc.sx = (short)f.buf0.x;
        f.desc.sy = (short)f.buf0.y;
        f.desc.sz = (short)f.buf0.z;
        func_ov022_02091324(global, &f.desc);
        angle = (angle + 0x5555) & 0xffff;
    }
}
