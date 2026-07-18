extern void func_ov022_020ad44c(void *out, int self);
extern void func_0202aa9c(int a);

typedef struct { int x, y, z; } Vec3;

typedef struct {
    char pad0[8];
    int kind;
    unsigned short flags;
    char pad0e[0x7a];
    unsigned short angle;
    char pad8a[0x26];
    Vec3 vec;
} Node;

void func_ov067_020b65f0(int self, Node *node) {
    Vec3 v;
    if (node->kind != 2 && node->kind != 3) return;
    func_ov022_020ad44c(&v, self);
    node->angle = (unsigned short)(*(unsigned short *)(*(int *)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
    node->flags |= 0x20;
    node->vec = v;
    func_0202aa9c((int)&node->flags);
}
