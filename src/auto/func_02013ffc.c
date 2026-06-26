struct S {
    int a;      /* 0x00 */
    int b;      /* 0x04 */
    int c;      /* 0x08 */
    char d;     /* 0x0c */
    int e;      /* 0x10 */
    int f;      /* 0x14 */
};

void func_02013ffc(struct S *p, int a1, int a2, int a3, int a4, int a5, int a6)
{
    p->b = a2;
    p->c = a3;
    p->d = (char)a4;
    p->a = a1;
    p->f = a5;
    p->e = a6;
}
