struct S {
    int a;          /* 0x00 */
    void *b;        /* 0x04 */
    int c;          /* 0x08 */
    int d;          /* 0x0c */
    struct S *e;    /* 0x10 */
    int f;          /* 0x14 */
    int g;          /* 0x18 */
    int h;          /* 0x1c */
    int i;          /* 0x20 */
    int j;          /* 0x24 */
};

void func_01fffc24(struct S *p)
{
    p->a = 0;
    p->b = &p->e;
    p->d = 0;
    p->c = 0;
    p->e = p;
    p->f = 0;
    p->h = 0;
    p->g = -1;
    p->i = 0;
    p->j = 0;
}
