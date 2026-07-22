/* Tear the scene down and, if the teardown reports finished, drop the running
 * flag. The installed teardown hook at +0x1ac answers directly; without one the
 * default path reports finished when func_ov002_02063888 returns 0.
 *
 * That negation is materialised as an if/else with 1 and 0 on separate branches,
 * which is what the ROM has -- written as `== 0` it folds into a predicated
 * pair. */
extern int func_ov002_02063888(void);

typedef struct {
    char pad0000[0x28];
    int nState;                     /* +0x28 */
    char pad002c[0x180];
    int (*pTeardownHook)(void);     /* +0x1ac */
} Ov002SceneContext;

extern Ov002SceneContext *data_ov002_0207f9fc;

void func_ov002_020673d4(void) {
    Ov002SceneContext *ctx = data_ov002_0207f9fc;
    int finished;

    if (ctx->pTeardownHook == 0) {
        if (func_ov002_02063888() == 0) {
            finished = 1;
        } else {
            finished = 0;
        }
    } else {
        finished = ctx->pTeardownHook();
    }

    if (finished != 0) {
        ctx->nState = 0;
    }
}
