/* Poll the session: reports 0 while no session is open, 1 when one is open but
 * has no poll hook installed, and otherwise whatever the hook says. */
typedef struct {
    char pad0000[0x8b4c];
    int nSessionHandle;         /* +0x8b4c, -1 = none */
    char pad8b50[0x44];
    int (*pPollHook)(void);     /* +0x8b94 */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

int func_ov002_0206aaa0(void) {
    Ov002RootContext *root = data_ov002_0207fa00;

    if (root->nSessionHandle != -1) {
        if (root->pPollHook == 0) {
            return 1;
        }

        return root->pPollHook();
    }

    return 0;
}
