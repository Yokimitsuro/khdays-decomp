/* Create the pause object once: while the slot at +0x8c94 still holds the empty
 * marker -1, quiesce with func_ov002_0206e718(0) and instantiate the class into
 * it. The 0x5c-byte parameter block is left uninitialised apart from word 1,
 * which carries the same -1. */
typedef struct {
    char pad0000[0x8c94];
    int nPauseObject;           /* +0x8c94, -1 = none */
} Ov002RootContext;

extern void func_ov002_0206e718(int mode);
extern int func_02023930(const void *cls, void *params);

extern Ov002RootContext *data_ov002_0207fa00;
extern char data_ov002_0207e8c8[];

void func_ov002_0206a048(void) {
    int params[23];
    Ov002RootContext *root = data_ov002_0207fa00;

    int *slot = &root->nPauseObject;

    if (*slot == -1) {
        params[1] = -1;
        func_ov002_0206e718(0);
        *slot = func_02023930(data_ov002_0207e8c8, params);
    }
}
