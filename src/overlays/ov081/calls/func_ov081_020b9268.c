extern int func_ov022_02095524(int a);
extern void func_ov081_020b9508(int a, int b);

typedef struct {
    char pad0[0x464];
    unsigned long long flags;
} Self;

void func_ov081_020b9268(Self *self, int *node, int arg) {
    int i;
    char *p;
    if (node[0] != 0 && (self->flags & 0x10000ULL) == 0) {
        if (func_ov022_02095524((int)self + 0x2f8 + 0x2000) == 0) node[0] = 0;
    }
    p = (char *)node + 0x14;
    for (i = 0; i < 7; i++, p += 0x10c) {
        func_ov081_020b9508((int)p, arg);
    }
}
