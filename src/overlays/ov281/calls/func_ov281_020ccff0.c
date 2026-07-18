extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(void *dst, void *src, int t);
extern void func_0202ed60(void *dst, void *src, int m);
extern void func_0202ef54(void *dst, void *a, void *b);
extern void func_0203c9d0(int a, void *b);

typedef struct { int x, y, z; } Vec3;

extern Vec3 data_02042264;
extern Vec3 data_02041dc8;

void func_ov281_020ccff0(int *ctx) {
    int b[4];
    int a[4];
    int *p = (int *)ctx[0];
    int *s = (int *)ctx[1];
    s[4] = func_0203d040(s[4], s[5], p[0xb] * 3, 0);
    func_0202f188(b, &data_02042264, s[4]);
    func_0202ed60(a, &data_02042264, s[0] + 0x124);
    func_0202ef54(a, a, b);
    func_0203c9d0(s[0] + 0xa0, a);
    {
        Vec3 *q = (Vec3 *)((char *)s + 0x20);
        *(Vec3 *)(s[0] + 0xf0) = *q;
        *q = data_02041dc8;
    }
}
