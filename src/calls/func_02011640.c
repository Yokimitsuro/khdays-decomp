extern int func_02011378(void *q);
extern void *func_02011548(void *q);
extern void func_020114fc(void *q);

extern char data_02047370[];

struct Node {
    void *x0;
    int x4;
    int x8;
    int xc;
};

struct Q {
    char _0[0x10];
    int x10;
};

int func_02011640(void *a, int b, int c, int d)
{
    struct Node *n;
    struct Q *q = (struct Q *)data_02047370;
    if (func_02011378(q) != 0) return 0;
    n = (struct Node *)func_02011548(q);
    n->x0 = a;
    n->x4 = c;
    n->x8 = b;
    n->xc = d;
    func_020114fc(q);
    q->x10 = q->x10 + n->xc;
    return 1;
}
