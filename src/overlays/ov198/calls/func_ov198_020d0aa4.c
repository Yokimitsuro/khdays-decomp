extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(void *dst, void *src, int t);
extern void func_0202ed60(void *dst, void *src, int m);
extern void func_0202ef54(void *dst, void *a, void *b);
extern void func_0203c9d0(int a, void *b);

typedef struct { int x, y, z; } Vec3;
extern Vec3 data_02042264;
extern Vec3 data_02041dc8;

void func_ov198_020d0aa4(int *self) {
    int b[4];
    int a[4];
    int *s = (int *)self[1];
    if ((*(unsigned char *)(*s + 0x1c4) & 2) == 0) {
        s[13] = func_0203d040(s[13], s[14], s[15], 0);
    }
    func_0202f188(b, &data_02042264, s[13]);
    func_0202ed60(a, &data_02042264, *s + 0x124);
    func_0202ef54(a, a, b);
    func_0203c9d0(*s + 0xa0, a);
    if (*(signed char *)(*s + 0x100 + 0xc6) != 0) {
        s[5] += (0x1800 - *(int *)(*s + 0x13c)) / 30;
    }
    {
        int owner = *s;
        s = (int *)((char *)s + 0x10);
        *(Vec3 *)(owner + 0xf0) = *(Vec3 *)s;
        *(Vec3 *)s = data_02041dc8;
    }
}
