extern void func_ov022_02091b48(int self, char *node, void *v, void *w);
extern int func_ov022_02091540(int a, int b);
extern void func_ov022_02091d80(int self, char *node, int c);

typedef struct { int x, y, z; } Vec3;
extern Vec3 data_02041dc8;

int func_ov104_020bba04(int self, char *node, int dt) {
    Vec3 a;
    Vec3 b;
    *(int *)(node + 4) += dt;
    a = *(Vec3 *)(node + 0xcc);
    *(Vec3 *)(node + 0xcc) = a;
    b = data_02041dc8;
    b.y += 0x25000;
    func_ov022_02091b48(self, node, &a, &b);
    node[2] = 2;
    if (func_ov022_02091540((int)(node + 0x28), dt) != 0) {
        node[2] = 3;
    }
    if (node[2] == 3) {
        *(int *)(node + 4) = 0;
        func_ov022_02091d80(self, node, 0);
    }
    return 0;
}
