/* The second parameter is FORWARDED, not used: it arrives in r1 and is handed to
 * the callee untouched, so it costs no instruction and is invisible in the
 * disassembly. Its only trace is that r1 is unavailable as a scratch register,
 * which shifts every other allocation up by one. */
/* Clamp the requested scroll position into [0, limit], remember it at +0x18c and
 * hand it to the scroller. Tail call.
 *
 * The two clamp arms are an if/else, not two independent ifs: overshooting the
 * limit skips the negative test entirely, which is what lets the ROM reuse the
 * limit it already loaded as the clamped value. */
extern int func_ov002_02064718(int position, int arg);

typedef struct {
    char pad0000[0x188];
    int nLimit;         /* +0x188 */
    int nPosition;      /* +0x18c */
} Ov002ScrollContext;

typedef struct {
    char pad0000[4];
    Ov002ScrollContext *pScroll;    /* +4 */
} Ov002ScrollRoot;

extern Ov002ScrollRoot data_ov002_0207f62c;

int func_ov002_02063660(int position, int arg) {
    Ov002ScrollContext *ctx = data_ov002_0207f62c.pScroll;
    int limit = ctx->nLimit;
    int result;

    if (position > limit) {
        result = limit;
    } else {
        if (position < 0) {
            position = 0;
        }
        result = position;
    }

    ctx->nPosition = result;
    return func_ov002_02064718(result, arg);
}
