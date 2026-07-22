/* Play the panel's confirm feedback, but only once the transition has finished
 * AND the panel actually has a target at +0x1a8 -- the two guards share one
 * predicated chain in the ROM. func_ov002_0205d658 has the final say. */
typedef struct {
    char pad00[0x1a8];
    int pTarget;            /* +0x1a8 */
} Ov002PanelContext;

extern int func_ov002_020573a4(void);
extern int func_ov002_0205d658(void);
extern void func_02033b78(int a, int b);

extern Ov002PanelContext *data_ov002_0207f614;

void func_ov002_02056cc8(void) {
    Ov002PanelContext *ctx = data_ov002_0207f614;

    if (func_ov002_020573a4() != 0 && ctx->pTarget != 0) {
        if (func_ov002_0205d658() != 0) {
            func_02033b78(0, 0);
        }
    }
}
