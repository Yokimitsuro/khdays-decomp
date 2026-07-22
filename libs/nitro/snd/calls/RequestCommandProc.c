/* Retries the PXI request until it is accepted. */
extern int func_020093e8(int a, int b, int c);

void RequestCommandProc(void) {
    int cmd = 7;
    int zero = 0;
    while (func_020093e8(cmd, zero, zero) < 0) {
        ;
    }
}
