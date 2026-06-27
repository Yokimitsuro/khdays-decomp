extern int  func_02011378(void *);
extern unsigned short func_02011358(void *, unsigned short);

typedef struct {
    char _pad[0xa];
    unsigned short f_a;   /* +0xa */
    unsigned short f_c;   /* +0xc */
} GfxCtx;

int func_020114fc(GfxCtx *p) {
    if (func_02011378(p) != 0) return 0;
    p->f_a = func_02011358(p, p->f_a);
    p->f_c = p->f_c + 1;
    return 1;
}
