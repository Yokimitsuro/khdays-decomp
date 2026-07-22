/* Take ownership of the load request's archive block (parking it at +0x20), hand
 * it and the id halfword at +0 to the sub-object at +0xc, reset the cursor, and
 * release the request with free=0 -- the context owns the block now.
 *
 * The block is stored and then RELOADED for the very next call rather than kept
 * in a register; caching it in a local costs the reload and the match. */
typedef struct {
    unsigned short wId;     /* +0x00 */
    char pad02[0xa];
    char aSub[0x14];        /* +0x0c passed by address */
    int nBlock;             /* +0x20 */
} Ov002PageContext;

extern int func_ov002_02052aec(int page);
extern void func_ov002_0206791c(void *sub, int block);
extern void func_ov002_02067948(void *sub, unsigned short id);
extern void func_ov002_0206716c(int a, int b);
extern void func_ov002_02052af4(int page, int freeBlock);

extern Ov002PageContext *data_ov002_0207f9fc;

void func_ov002_020674f4(int page) {
    Ov002PageContext *ctx = data_ov002_0207f9fc;

    ctx->nBlock = func_ov002_02052aec(page);
    func_ov002_0206791c(ctx->aSub, ctx->nBlock);
    func_ov002_02067948(ctx->aSub, ctx->wId);
    func_ov002_0206716c(0, 0);
    func_ov002_02052af4(page, 0);
}
