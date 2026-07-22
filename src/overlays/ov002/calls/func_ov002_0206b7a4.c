/* Run the root's shutdown hook and report its verdict. With no root, or no hook
 * installed, the answer is yes -- there is nothing left to wait for. */
typedef struct {
    char pad0000[0x8ba4];
    int (*pShutdownHook)(void);     /* +0x8ba4 */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

int func_ov002_0206b7a4(void) {
    Ov002RootContext *root = data_ov002_0207fa00;

    if (root == 0 || root->pShutdownHook == 0) {
        return 1;
    }

    return root->pShutdownHook();
}
