extern void func_02011eb4(void *);

typedef struct {
    int f0;     /* +0x00 */
    int f4;     /* +0x04 */
    int f8;     /* +0x08 */
    int fc;     /* +0x0c */
    int f10;    /* +0x10 */
    int f14;    /* +0x14 */
    int f18;    /* +0x18 */
    int f1c;    /* +0x1c */
    char rest[0]; /* +0x20 sub-struct */
} GfxState;

void func_02011e74(GfxState *p) {
    func_02011eb4((char *)p + 0x20);
    p->f0  = 0;
    p->f4  = 0;
    p->f8  = 0;
    p->fc  = 1;
    p->f10 = 0;
    p->f14 = 0x1000;
    p->f18 = 0;
    p->f1c = 0;
}
