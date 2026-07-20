/* Scene entry for the four-row list: take the root heap block as the context,
 * open the archive named by data_ov022_020b290c, and give each of the four rows
 * its resource -- but only for the rows func_02023588(0x20ee) admits, and the
 * bFirst flag tells func_ov002_02050d18 which admitted row is the first one.
 * Every row clears its own resource pointer first, so a rejected row keeps null.
 * Ten interpolators are initialised: two per row, plus header, footer and cursor.
 * The archive handle is a scratch buffer and is freed before returning the next
 * scene step.
 *
 * func_ov002_02050d18 is declared with FOUR parameters here even though its own
 * matched body only reads two -- this call site sets r0..r3, and a callee's body
 * can never settle its arity, only its callers can. */
typedef struct {
    char pad00[0x2c];
    void *pResource;        /* +0x2c -- what func_ov002_02050d18 stores */
} Ov022Row;                 /* 0x30 */

typedef struct {
    Ov022Row rows[4];       /* +0x000 */
    unsigned char bReady;   /* +0x0c0 */
    char padc1[7];
    int tweenHeader[7];     /* +0x0c8 */
    int tweenFooter[7];     /* +0x0e4 */
    int aRowTweenA[4][7];    /* +0x100 */
    int aRowTweenB[4][7];    /* +0x170 */
    int tweenCursor[7];     /* +0x1e0 */
} Ov022RootContext;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern char *func_02024e6c(char *path);
extern void *func_0201ef9c(char *path, int heap);
extern void func_0201f390(int phase);
extern void func_02025138(void *arc);
extern int func_02023588(int cue);
extern int func_ov002_02050d18(Ov022Row *row, void *arc, int bFirst, int index);
extern void func_02035f84(void *tween);
extern void func_ov022_02086970(void);

extern void *data_ov022_020b2e74;
extern char data_ov022_020b290c[];

void *func_ov022_02086894(void) {
    Ov022RootContext *ctx = NNSi_FndGetCurrentRootHeap();
    void *arc;
    int bFirst = 1;
    int i;

    (&data_ov022_020b2e74)[0] = ctx;
    ctx->bReady = 0;
    arc = func_0201ef9c(func_02024e6c(data_ov022_020b290c), 0xf);
    func_0201f390(0);
    func_02025138(arc);
    func_0201f390(1);
    for (i = 0; i < 4; i++) {
        ctx->rows[i].pResource = 0;
        func_02035f84(ctx->aRowTweenA[i]);
        func_02035f84(ctx->aRowTweenB[i]);
        if (func_02023588(0x20ee) == 0) {
            func_ov002_02050d18(&ctx->rows[i], arc, bFirst, i);
            bFirst = 0;
        }
    }
    func_02035f84(ctx->tweenHeader);
    func_02035f84(ctx->tweenFooter);
    func_02035f84(ctx->tweenCursor);
    NNSi_FndFreeFromDefaultHeap(arc);
    return (void *)&func_ov022_02086970;
}
