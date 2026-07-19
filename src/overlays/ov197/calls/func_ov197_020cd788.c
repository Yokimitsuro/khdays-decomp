extern void VEC_Subtract(void *a, int b, void *out);
extern void func_01ff8d18(void *a, void *b);
extern int func_020050b4(int a, int b);
extern void func_ov197_020cca1c(int *s, int b, int c);
extern void func_0203c634(int *self, int idx, void *cb);
extern void func_ov197_020cd868(void);

typedef struct { int x, y, z; } Vec3;
extern Vec3 data_02041dc8;

void func_ov197_020cd788(int *self) {
    Vec3 v;
    int *s = (int *)self[1];
    int p;
    v = data_02041dc8;
    p = *(int *)(*s + 0x394);
    if (p != 0) {
        v = *(Vec3 *)(p + 0x74);
        v.y += *(int *)(*(int *)(*s + 0x398) + 0x80);
        VEC_Subtract(&v, *s + 0x3d8, &v);
        func_01ff8d18(&v, &v);
        s[0xe] = func_020050b4(v.x, v.z);
    }
    s[0x10] += *(int *)(*self + 0x2c);
    if (s[0x10] < 0x1188) return;
    func_ov197_020cca1c(s, v.y, *s + 0x3d8);
    func_0203c634(self, *(signed char *)((char *)self + 0x20), (void *)&func_ov197_020cd868);
}
