extern int func_0202552c(void *p);
extern int func_020163f4(void *p);

struct S {
    short _0;
    unsigned short x2;
    unsigned short x4;
    char _6[6];
    void *xc;
};

int func_0201f6b0(struct S *p)
{
    p->x2 = p->x2 - 1;
    if (p->x2 == 0) {
        if (*(int *)p->xc == 0x4850414B) {
            func_0202552c(p->xc);
        } else {
            func_020163f4(p->xc);
        }
        p->x4 = 0;
        return 1;
    }
    return 0;
}
