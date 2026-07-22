/* Point the scene's tile surface at +0x6c at the item held in +0xb8, but only
 * once func_ov002_020573cc reports the transition finished. The relayout at
 * func_ov002_0205932c runs first, so the surface is retargeted against fresh
 * geometry. */
typedef struct {
    char pad00[0x6c];
    char surface[0x3c];     /* +0x6c TileSurface */
    char pada8[0x10];
    int pCurrentItem;       /* +0xb8 */
} Ov002PanelContext;

extern int func_ov002_020573cc(void);
extern void func_ov002_0205932c(void);
extern void func_02030094(void *surface, int item, int a);

extern Ov002PanelContext *data_ov002_0207f614;

void func_ov002_02056b70(void) {
    Ov002PanelContext *ctx = data_ov002_0207f614;

    if (func_ov002_020573cc() != 0) {
        return;
    }

    func_ov002_0205932c();
    func_02030094(ctx->surface, ctx->pCurrentItem, 1);
}
