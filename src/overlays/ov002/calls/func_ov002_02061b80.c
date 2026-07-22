/* Is the panel in a real mode? Reports the caller's fallback when there is no
 * panel installed at all, which is why the null path leaves r0 alone instead of
 * loading a constant. */
typedef struct {
    char pad0000[0xd58];
    int nMode;      /* +0xd58, -1 = none */
} Ov002PanelContext;

extern Ov002PanelContext *data_ov002_0207f628;

int func_ov002_02061b80(int fallback) {
    Ov002PanelContext *ctx = data_ov002_0207f628;

    if (ctx == 0) {
        return fallback;
    }

    return ctx->nMode != -1;
}
