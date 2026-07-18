extern void func_ov095_020bb5f0(int self, int kind, void *out);
extern void func_0202aa9c(int a);

typedef struct { int x, y, z; } Vec3;

typedef struct {
    signed char f0;
    signed char f1;
    char pad2[2];
    unsigned short flags;
    char pad6[0x7a];
    unsigned short angle;
    char pad82[0x26];
    Vec3 vec;
} Node;

void func_ov095_020bb57c(int self, Node *node) {
    Vec3 v;
    if (node->f1 != 2) return;
    func_ov095_020bb5f0(self, node->f0, &v);
    node->angle = (unsigned short)(*(unsigned short *)(*(int *)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
    node->flags |= 0x20;
    node->vec = v;
    func_0202aa9c((int)&node->flags);
}
