extern void func_0202aa9c(int a);

typedef struct { int x, y, z; } Vec3;

typedef struct {
    char pad0[0x4c];
    unsigned short flags;
    char pad4e[0x7a];
    unsigned short angle;
    char padca[0x26];
    Vec3 vec;
    char padfc[0x158 - 0xfc];
    int kind;
} Node;

typedef struct { char pad0[0x200]; Node node; } Block;

void func_ov086_020b8eac(int self, Block *b) {
    Vec3 v;
    if (b->node.kind != 2 && b->node.kind != 3 && b->node.kind != 4) return;
    v = *(Vec3 *)(self + 0x8c + 0x400);
    b->node.angle = (unsigned short)(*(unsigned short *)(*(int *)(self + 0x20) + 0x80) - 0x8000) + 0x8000;
    b->node.flags |= 0x20;
    b->node.vec = v;
    func_0202aa9c((int)&b->node.flags);
}
