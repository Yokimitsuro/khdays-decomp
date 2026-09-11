extern void *OS_IsThreadAvailable_0x020c9848(void);
extern int func_ov022_02083f0c(void);

typedef struct {
    unsigned short flags;
} Node;

typedef struct {
    int flag40 : 1;
} Flags40;

typedef struct {
    char pad[0x74];
    void (*handler)(int ctx, int b, int a);
} Thread;

int func_ov107_020c0b14(void *self, int a2) {
    Node *p = *(Node **)((char *)self + 4);
    Thread *t;
    int a, b, ctx;

    if (p != 0 && (p->flags & 4) && ((Flags40 *)((char *)p + 0x40))->flag40) {
        t = OS_IsThreadAvailable_0x020c9848();
        if (t->handler != 0) {
            a = (a2 >= 0) ? a2 : 0;
            b = (a2 >= 0) ? 3 : 0;

            t = OS_IsThreadAvailable_0x020c9848();
            ctx = func_ov022_02083f0c();
            (*(void (**)(int, int, int))&t->handler)(ctx, b, a);
        }
    }
    return 0;
}
