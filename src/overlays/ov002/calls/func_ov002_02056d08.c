/* Play the panel's cancel feedback, but only once the transition has finished
 * AND the panel has a target at +0x1a8 -- the ROM folds both guards into one
 * predicated chain. func_ov002_0205d478 has the final say. Sibling of
 * func_ov002_02056cc8, which is the same shape against func_ov002_0205d658. */
typedef struct {
    char pad00[0x1a8];
    int pTarget;            /* +0x1a8 */
} Ov002PanelContext;

extern int func_ov002_020573a4(void);
extern int func_ov002_0205d478(void);
extern void func_02033b78(int a, int b);

extern Ov002PanelContext *data_ov002_0207f614;

void func_ov002_02056d08(void) {
    Ov002PanelContext *ctx = data_ov002_0207f614;

    if (func_ov002_020573a4() != 0 && ctx->pTarget != 0) {
        if (func_ov002_0205d478() != 0) {
            func_02033b78(0, 0);
        }
    }
}
