/*
 * Ov002_SetPanelMode - choose which set of per-frame hooks the panel runs, and
 * park the layers they drive.
 *
 * Mode zero is the main-screen panel: BG1 and BG3 of the main engine are put
 * at horizontal 0, vertical 0x18, and all four hooks are installed. Any other
 * mode is the sub-screen one: BG0 and BG1 of the sub engine get the same
 * offsets and only the first two hooks are installed, the other two cleared.
 * The mode is remembered last.
 *
 * ARM.
 */

typedef unsigned int u32;

typedef struct {
    char pad0000[0x60];
    int nPanelMode;                     /* +0x060 */
    char pad0064[0x1cc];
    void *apHandlers[4];                /* +0x230 */
} Ov002PanelCtx;

extern Ov002PanelCtx *data_ov002_0207f614;

extern void func_ov002_020558b0(void);
extern void func_ov002_020558d8(void);
extern void func_ov002_02054e2c(void);
extern void func_ov002_02055888(void);
extern void func_ov002_02055900(void);
extern void func_ov002_02055934(void);

void func_ov002_020557f4(int nMode)
{
    Ov002PanelCtx *ctx;
    volatile u32 *pOfs;

    ctx = data_ov002_0207f614;
    if (nMode != 0) {
        pOfs = (volatile u32 *)0x04001010;
        pOfs[0] = 0x180000;
        pOfs[1] = 0x180000;
        ctx->apHandlers[0] = (void *)func_ov002_020558b0;
        ctx->apHandlers[1] = (void *)func_ov002_020558d8;
        ctx->apHandlers[2] = 0;
        ctx->apHandlers[3] = 0;
    } else {
        pOfs = (volatile u32 *)0x04000014;
        pOfs[0] = 0x180000;
        pOfs[2] = 0x180000;
        ctx->apHandlers[0] = (void *)func_ov002_02054e2c;
        ctx->apHandlers[1] = (void *)func_ov002_02055888;
        ctx->apHandlers[2] = (void *)func_ov002_02055900;
        ctx->apHandlers[3] = (void *)func_ov002_02055934;
    }
    ctx->nPanelMode = nMode;
}
