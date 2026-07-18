extern void func_0202aa9c(int a);

typedef struct { int x, y, z; } Vec3;

typedef struct {
    int kind;
    unsigned short flags;
    char pad6[0x7a];
    unsigned short angle;
    char pad82[0x24];
    Vec3 vec;
} Node;

void func_ov097_020bb93c(int self, Node *node) {
    if (node->kind != 2) return;
    node->angle = (unsigned short)(*(unsigned short *)(*(int *)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
    node->flags |= 0x20;
    node->vec = *(Vec3 *)(self + 0x104 + 0x800);
    func_0202aa9c((int)&node->flags);
}
