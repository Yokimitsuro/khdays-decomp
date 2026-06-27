extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int mask);

struct Y {
    char _0[0x1c];
    int oflags;
};

struct X {
    char _0[8];
    struct Y *other;
    int flags;
};

void func_0200adf4(struct X *p) {
    int mask;
    int test;
    mask = OS_DisableInterrupts();
    test = p->flags & 1 ? 1 : 0;
    if (test != 0) {
        p->flags = p->flags | 2;
        p->other->oflags = p->other->oflags | 0x20;
    }
    OS_RestoreInterrupts(mask);
}
