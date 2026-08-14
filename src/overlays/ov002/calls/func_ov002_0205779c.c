/* Draws one tween cell of the first gauge.
 *
 * While the scene is holding a value, a cell at or below the held count is
 * drawn in the third style instead of the caller's, which is what dims the part
 * of the bar that is about to drain. The style table has six bytes per entry
 * and the row helper is asked for that same six-byte span. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 pad0000[6];
} Ov002GaugeStyle;

typedef struct {
    u8 pad0000[0x34];
    int bHolding;                       /* +0x34 */
    u16 wHeldCount;                     /* +0x38 */
} Ov002SceneCtx;

extern Ov002SceneCtx *data_ov002_0207f618;
extern Ov002GaugeStyle data_ov002_0207dde4[];

extern void func_ov002_020576d8(int nHandle, int nCell, int nSize, int nCode,
                                int nA, int nB, Ov002GaugeStyle *pStyle);

void func_ov002_0205779c(int nHandle, int nCell, int nMode) {
    Ov002SceneCtx *ctx = data_ov002_0207f618;

    if (ctx->bHolding != 0 && nMode == 0) {
        if (nCell <= ctx->wHeldCount) {
            nMode = 3;
        }
    }
    func_ov002_020576d8(nHandle, nCell, 6, 0x4d, 1, 0, &data_ov002_0207dde4[nMode]);
}
