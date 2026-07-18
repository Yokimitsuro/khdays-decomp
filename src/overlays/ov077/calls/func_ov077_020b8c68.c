extern void func_0202aa9c(int a);

typedef struct { int x, y, z; } Vec3;

typedef struct {
    char pad0[0xc];
    int kind;
    unsigned short flags;
    char pad12[0x7a];
    unsigned short angle;
    char pad8e[0x26];
    Vec3 vec;
} Node;

void func_ov077_020b8c68(int self, Node *node) {
    Vec3 v;
    if (node->kind != 1) return;
    v = *(Vec3 *)(self + 0x8c + 0x400);
    node->angle = (unsigned short)(*(unsigned short *)(*(int *)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
    node->flags |= 0x20;
    node->vec = v;
    func_0202aa9c((int)&node->flags);
}
