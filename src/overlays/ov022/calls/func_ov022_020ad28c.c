extern void func_ov022_02092588(int arg0, void *buf, int arg2, int arg3);

typedef struct { int a; int b; int c; } Vec3w;

void func_ov022_020ad28c(int arg0, unsigned int *arg1, unsigned short arg2, int arg3) {
    struct {
        unsigned char b0;
        unsigned char pad0[3];
        unsigned int w4;
        unsigned int w8;
        unsigned int wc;
        unsigned short h10;
        unsigned short h12;
        unsigned char b14;
        unsigned char b15;
        unsigned short h16;
        unsigned short h18;
        unsigned char pad1[2];
    } buf;
    buf.b0 = *(unsigned char *)(arg0 + 9);
    *(Vec3w *)&buf.w4 = *(Vec3w *)arg1;
    buf.h10 = 0;
    buf.h12 = 0;
    buf.b14 = 0;
    buf.b15 = 0;
    buf.h16 = arg2;
    buf.h18 = (unsigned short)arg3;
    func_ov022_02092588(arg0 + 0x2648, &buf, 0, arg3);
}
