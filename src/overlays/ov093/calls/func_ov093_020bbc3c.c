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

typedef struct { char pad[0x11c]; Node node; } Block;

void func_ov093_020bbc3c(int self, Block *b) {
    if (b->node.kind != 2) return;
    b->node.angle = (unsigned short)(*(unsigned short *)(*(int *)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
    b->node.flags |= 0x20;
    b->node.vec = *(Vec3 *)(self + 0x104 + 0x800);
    func_0202aa9c((int)&b->node.flags);
}
