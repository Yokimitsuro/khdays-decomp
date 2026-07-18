extern void func_0202aa9c(int a);

typedef struct { int x, y, z; } Vec3;

typedef struct {
    int kind;
    unsigned short flags;
    char pad6[0x7a];
    unsigned short angle;
    char pad82[0x26];
    Vec3 vec;
} Node;

void func_ov094_020bb700(int self, Node *node) {
    Vec3 v;
    if (node->kind != 2 && node->kind != 3 && node->kind != 4) return;
    v = *(Vec3 *)(self + 0x8c + 0x400);
    node->angle = (unsigned short)(*(unsigned short *)(*(int *)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
    node->flags |= 0x20;
    node->vec = v;
    func_0202aa9c((int)&node->flags);
}
