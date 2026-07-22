/* Constant-argument forwarding veneer onto FSi_ReadFileCore (fourth argument 0). */
extern void *FSi_ReadFileCore();

void *OS_UnlockByWord_0x0200ae4c(int a, void *b, void *c) {
    return FSi_ReadFileCore(a, b, c, 0);
}
