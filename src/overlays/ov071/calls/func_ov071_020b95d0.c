extern int func_ov022_02095524(int a);
extern void MI_Copy48B(int dst, int src);
extern int func_0202a818(int a, int b);
extern void func_ov071_020b9914(int a, int b);

typedef struct {
    char pad0[0x464];
    unsigned long long flags;
    char pad46c[0x2aba - 0x46c];
    short f2aba;
} Self;

void func_ov071_020b95d0(Self *self, int *node) {
    int i;
    char *p;
    if (node[0] == 2 && (self->flags & 0x10000ULL) == 0) {
        if (func_ov022_02095524((int)self + 0x2f8 + 0x2000) == 0) node[0] = 0;
    }
    if (node[0] == 1) {
        MI_Copy48B((int)self + 0x158 + 0x400, (int)node + 0x8c);
        if (func_0202a818((int)node + 0xc, self->f2aba) != 0) {
            node[0] = 2;
        }
    }
    for (i = 0, p = (char *)node + 0x118; i < 6; i++, p += 0x110) {
        func_ov071_020b9914((int)p, self->f2aba);
    }
}
