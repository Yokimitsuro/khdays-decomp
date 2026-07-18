extern void func_ov022_020ad44c(void *out, int self);
extern void func_0202aa9c(int a);

typedef struct { int x, y, z; } Vec3;

typedef struct {
    char pad0[0x24];
    int kind;
    unsigned short flags;
    char pad2a[0x7a];
    unsigned short angle;
    char pada6[0x26];
    Vec3 vec;
} Node;

typedef struct { char pad0[0x100]; Node node; } Block;

void func_ov096_020bb240(int self, Block *b) {
    Vec3 v;
    if (b->node.kind != 1) return;
    func_ov022_020ad44c(&v, self);
    b->node.angle = (unsigned short)(*(unsigned short *)(*(int *)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
    b->node.flags |= 0x20;
    b->node.vec = v;
    func_0202aa9c((int)&b->node.flags);
}
