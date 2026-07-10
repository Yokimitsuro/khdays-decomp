extern void func_ov022_020a1cd8(int arg0, void *arg1, int arg2);

typedef struct { int a; int b; int c; } Vec3w;

void func_ov022_020a1c28(int arg0, int *arg1, int arg2, int arg3) {
    struct { int w0; int w1; int w2; int w3; int w4; int w5; int w6; int w7; } buf;
    *(Vec3w *)&buf.w0 = *(Vec3w *)arg1;
    *(Vec3w *)&buf.w3 = *(Vec3w *)(arg1 + 5);
    buf.w6 = arg1[3];
    buf.w7 = arg1[4];
    func_ov022_020a1cd8(arg0, &buf, arg2);
}
