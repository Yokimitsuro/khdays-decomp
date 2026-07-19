extern int func_0202aef8(int a, int b);
extern void func_ov022_02091b48(int self, char *node, void *v, void *w);
extern int func_ov022_02091540(int a, int b);
extern void func_ov022_02091d80(int self, char *node, int c);

typedef struct { int x, y, z; } Vec3;
extern Vec3 data_02041dc8;

int func_ov039_020b44fc(int self, char *node, int dt) {
    Vec3 a;
    Vec3 b;
    int r = func_0202aef8((int)(node + 0x28), 0);
    int lim = r - 0x9000;
    a = *(Vec3 *)(node + 0xcc);
    b = data_02041dc8;
    *(int *)(node + 4) += dt;
    if (*(int *)(node + 4) <= lim) {
        func_ov022_02091b48(self, node, &a, &b);
    }
    if (node[2] == 3) {
        node[2] = 4;
    }
    if (func_ov022_02091540((int)(node + 0x28), dt) != 0) {
        node[2] = 3;
    }
    if (node[2] == 3) {
        *(int *)(node + 4) = 0;
        func_ov022_02091d80(self, node, 0);
    }
    return 0;
}
