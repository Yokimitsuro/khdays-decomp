extern void *func_0202c268(int a, void *b, void *c, int d);
extern void func_01ffd0e8(int a, void *b, void *c, void *d);
extern int data_ov104_020bc2a0;

typedef struct { int x, y, z; } Vec3;

void func_ov104_020bb8a4(Vec3 *src, int *out) {
    Vec3 a;
    int q[3];
    void *r;
    int *ctx;
    a = *src;
    *(Vec3 *)out = a;
    a.y += 0x25000;
    q[0] = 0;
    q[1] = -0x4a000;
    q[2] = 0;
    ctx = *(int **)&data_ov104_020bc2a0;
    r = func_0202c268(*(unsigned short *)((char *)ctx + 0x66), &a, q, ctx[8]);
    if (r == 0) {
        out[1] -= 0x25000;
        return;
    }
    func_01ffd0e8(*(int *)((char *)r + 0xc), q, &a, out);
    out[1] += 0x333;
}
