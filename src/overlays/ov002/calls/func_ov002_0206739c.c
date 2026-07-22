/* Ask whether the page may close: through the installed hook at +0x1ac when
 * there is one, otherwise by asking func_ov002_02063888 and inverting it. On a
 * yes, notify with the page id and park the state at 3. */
typedef struct {
    char pad00[2];
    unsigned short wId;     /* +0x02 */
    char pad04[0x24];
    int nState;             /* +0x28 */
    char pad2c[0x180];
    int (*pfnCanClose)(void); /* +0x1ac */
} Ov002PageContext;

extern int func_ov002_02063888(void);
extern void func_ov002_0206716c(unsigned short id, int a);

extern Ov002PageContext *data_ov002_0207f9fc;

void func_ov002_0206739c(void) {
    Ov002PageContext *ctx = data_ov002_0207f9fc;
    int ok;

    if (ctx->pfnCanClose == 0) {
        ok = func_ov002_02063888() == 0;
    } else {
        ok = ctx->pfnCanClose();
    }

    if (ok != 0) {
        func_ov002_0206716c(ctx->wId, 1);
        ctx->nState = 3;
    }
}
