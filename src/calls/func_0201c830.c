extern void *func_0201a4c4(void *handle, int b, int d);
extern void *func_0201a62c(int index, void *parent);
extern int func_0201bd30(int c, int six, void *prev, int zero, int *local);
extern void WM_EndKeySharing_0x0201a55c(void *p);
extern void func_0201a568(void *r5, void *p, int v, int local);
extern void func_0201a110(void *a, int b);
extern void func_0201a150(void *a, int b);
extern void func_0201a1e4(void *a, int g, int h);

typedef struct {
    int _0;
    int _4;
    int _8;
    int _c;
    int _10;
    int _14;
    int _18;
} F_0201c830;

typedef struct {
    int _0;
    char _4;
    char _5;
    unsigned char _6;
    unsigned char _7;
} E_0201c830;

int func_0201c830(void *a, int b, int c, int d, E_0201c830 *e, F_0201c830 *f, int g, int h)
{
    void *r5;
    void *tmp;
    int local;

    r5 = func_0201a4c4(a, b, d);
    if (r5 == 0)
        return 0;

    tmp = func_0201a62c(b, r5);

    if (func_0201bd30(c, 6, tmp, 0, &local) != 0) {
        WM_EndKeySharing_0x0201a55c(r5);
        return 0;
    }

    func_0201a568(r5, (char *)f + f->_18, e->_0, local);
    func_0201a110(a, e->_6);
    func_0201a150(a, e->_7);
    func_0201a1e4(a, g, h);
    return 1;
}
