/* Release the pending request at +0x660, if there is a context and a request to
 * release. The sub-object at +0xc does the actual teardown; the slot is cleared
 * afterwards so a second call is a no-op. */
extern void func_ov002_02052464(void *sub);

typedef struct {
    char pad0000[0xc];
    char sub[0x654];        /* +0xc */
    void *pRequest;         /* +0x660 */
} Ov002RequestContext;

extern Ov002RequestContext *data_ov002_0207f624;

void func_ov002_0205eb78(void) {
    Ov002RequestContext *ctx = data_ov002_0207f624;

    if (ctx == 0) {
        return;
    }

    if (ctx->pRequest == 0) {
        return;
    }

    func_ov002_02052464(ctx->sub);
    ctx->pRequest = 0;
}
