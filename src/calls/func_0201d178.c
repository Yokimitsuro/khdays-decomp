extern void func_0201d214(void *p);
extern void func_0201d298(void *list, void *node);
extern void func_0201cdec(void *p);

extern char data_0204b620[];
extern char *data_0204ad8c[];

struct S {
    char _0[0x110];
    int flags;
    char _114[0x168 - 0x114];
    void (*x168)(void *);
};

void func_0201d178(struct S *p)
{
    char *q;
    if (((p->flags << 31) >> 31) == 0) return;
    func_0201d214(p);
    p->x168(p);
    func_0201d298(data_0204b620, p);
    q = data_0204ad8c[1];
    if (q != 0) {
        func_0201d298(q + 0x4e0, p);
    }
    func_0201cdec(p);
}
