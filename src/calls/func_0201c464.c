struct S { int a; int b; };
struct L { unsigned char b0; unsigned char b1; unsigned short h2; unsigned short h4; unsigned short h6; int pad; };

extern void SND_GetFirstInstDataPos(struct S *p);
extern int func_02009044(int bank, struct L *out, struct S *cur);
extern int func_0201c39c(void *a, unsigned short h, int d, int e);

int func_0201c464(void *a, int bank, int c, int d, int e)
{
    struct L sec;
    struct S cur;
    struct S s;

    SND_GetFirstInstDataPos(&s);
    cur = s;
    if (bank == 0) return 0;
    while (func_02009044(bank, &sec, &cur)) {
        if (sec.b0 == 1 && c == sec.h4) {
            if (!func_0201c39c(a, sec.h2, d, e)) return 0;
        }
    }
    return 1;
}
