extern void VEC_Subtract(const void *a, const void *b, void *out);
extern void func_ov022_020a1cd8(int arg0, void *arg1, int arg2);

typedef struct { int a; int b; int c; } Vec3w;

void func_ov022_020a1c80(int arg0, int *arg1, int arg2, int arg3) {
    struct { int w0; int w1; int w2; int v[3]; int w6; int w7; } buf;
    *(Vec3w *)&buf.w0 = *(Vec3w *)arg1;
    buf.w6 = arg1[7];
    buf.w7 = arg1[6];
    VEC_Subtract(arg1 + 3, arg1, buf.v);
    func_ov022_020a1cd8(arg0, &buf, arg2);
}
