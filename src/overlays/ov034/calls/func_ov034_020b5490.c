extern void func_ov022_020ad44c(void *out, int self);
extern void func_0202aa9c(int a);

typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned char b0 : 1; } Flags;

void func_ov034_020b5490(int self, int *node) {
    Vec3 v;
    int ok = 0;
    if (!((Flags *)(self + 0x694))->b0) return;
    switch (node[9]) {
    case 5:
        v = *(Vec3 *)(self + 0x8c + 0x400);
        v.y += 0xf33;
        ok = 1;
        break;
    case 2:
        func_ov022_020ad44c(&v, self);
        ok = 1;
        break;
    case 4:
        v = *(Vec3 *)(self + 0x8c + 0x400);
        ok = 1;
        break;
    }
    if (ok == 0) return;
    *(Vec3 *)((char *)node + 0xcc) = v;
    func_0202aa9c((int)node + 0x28);
}
