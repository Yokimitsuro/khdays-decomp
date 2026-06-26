struct S {
    char pad[0x4c];
    int a;     /* 0x4c */
    int b;     /* 0x50 */
    int c;     /* 0x54 */
    int d;     /* 0x58 */
    int e;     /* 0x5c */
    int f;     /* 0x60 */
    int g;     /* 0x64 */
    int arr[14]; /* 0x68 */
};

void func_ov005_0204ee2c(struct S *p)
{
    int i;

    p->a = (p->a > 99) ? 99 : p->a;
    p->b = (p->b > 999) ? 999 : p->b;
    p->c = (p->c > 999) ? 999 : p->c;
    p->d = (p->d > 999) ? 999 : p->d;
    p->e = (p->e > 999) ? 999 : p->e;
    p->f = (p->f > 0x64000) ? 0x64000 : p->f;
    p->g = (p->g > 255) ? 255 : p->g;

    for (i = 0; i < 14; i++) {
        if (p->arr[i] > 0x64000) p->arr[i] = 0x64000;
    }
}
