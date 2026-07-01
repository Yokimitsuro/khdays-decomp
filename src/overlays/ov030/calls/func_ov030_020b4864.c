typedef long long s64;

extern int func_ov022_020ad44c();
extern int func_ov022_020a23a4();
extern int func_ov022_020a0fb8();
extern int func_020307f4();
extern int func_0203084c();
extern int func_ov022_0209246c();

extern short data_0203d210[];

struct Vec3 { int x, y, z; };

struct StructB {
    int f00;
    int f04;
    int f08;
    int f0c;
    unsigned char f10;
    unsigned char pad11[3];
    int f14;
    int f18;
    int f1c;
    int f20;
    unsigned char pad24;
    unsigned char f25;
    unsigned char pad26[2];
};

struct StructOut {
    char head[0xc];
    int f0c;
    int f10;
    int f14;
    int f18;
    int f1c;
    int f20;
    int f24;
    int f28;
};

struct StructM {
    unsigned char f00;
    unsigned char pad01[3];
    struct Vec3 f04;
    unsigned short f10;
    unsigned short f12;
    unsigned char f14;
    unsigned char f15;
    unsigned short f16;
    unsigned short f18;
};

void func_ov030_020b4864(char *this) {
    char *p = *(char **)(this + 0xdb4);
    int v = *(int *)(p + 0x7b0);
    int ok;
    int idx, angle;
    struct StructOut so;
    struct StructB sb;
    struct StructM sm;
    struct Vec3 tmp;
    unsigned char b;

    if (v % 3 != 0) {
        return;
    }

    switch (v) {
    case 0x9000: case 0xf000: case 0x15000: case 0x1b000:
    case 0x21000: case 0x27000: case 0x33000: case 0x3c000:
    case 0x4b000:
        ok = 1;
        break;
    default:
        ok = 0;
        break;
    }
    if (ok == 0) {
        return;
    }

    func_ov022_020ad44c(&so, p);

    angle = (unsigned short)(*(unsigned short *)(*(char **)(p + 0x20) + 0x80) - 0x8000);
    idx = angle >> 4;
    so.f0c = 0x2800;
    so.f10 = *(short *)(p + 0x66);
    so.f14 = -data_0203d210[idx * 2];
    so.f18 = 0;
    so.f1c = -data_0203d210[idx * 2 + 1];
    so.f20 = 0x1000;
    so.f24 = 0;
    so.f28 = 0;

    {
        int arg = 0x13b0;
        sb.f08 = 0x205;
        if (*(int *)this != 0) {
            sb.f08 = 0x205 | 0x420;
            arg = 0x12c0;
        }
        func_ov022_020a23a4(p, arg, &sb.f00, &sb.f04);
    }

    sb.f0c = 0;
    sb.f14 = 0xa00;
    sb.f18 = 0x66;
    sb.f1c = 0xa00;
    sb.f20 = 0;
    sb.f10 = 0;
    b = (sb.f25 & ~1) & 0xff;
    b = b & ~2;
    sb.f25 = b;

    if (func_ov022_020a0fb8(p, &so, &sb.f00, b) == 0) {
        return;
    }

    if (*(int *)(p + 0x26bc) & 1) {
        return;
    }
    if (*(int *)(p + 0x26bc) & 0x40) {
        return;
    }

    sm.f14 = func_020307f4(3);

    tmp = *(struct Vec3 *)(p + 0x26c8);
    tmp.x += (int)(((s64)(func_0203084c() - 0x800) * 0x99a + 0x800) >> 12);
    tmp.y += (int)(((s64)(func_0203084c() - 0x800) * 0x4cd + 0x800) >> 12);
    tmp.z += (int)(((s64)(func_0203084c() - 0x800) * 0x99a + 0x800) >> 12);

    sm.f00 = *(unsigned char *)(p + 9);
    sm.f04 = tmp;
    sm.f10 = 0x1000;
    sm.f12 = (unsigned short)angle;
    sm.f15 = 1;
    sm.f16 = *(short *)(p + 0x7a6);
    sm.f18 = 0;

    func_ov022_0209246c(p + 0x2648, 5, &sm);

    if (*(signed char *)(p + 0x47a) != -1) {
        return;
    }
    if ((*(int *)p & 0x10000) == 0) {
        *(unsigned char *)(p + 0x47a) = 3;
        *(unsigned char *)(p + 0x47b) = 0;
    }
}
