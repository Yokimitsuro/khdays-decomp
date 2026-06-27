extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern int *data_02044748[];

int *func_02008ba4(void) {
    int mask;
    int *h;
    int *n;
    mask = OS_DisableInterrupts();
    h = data_02044748[0];
    if (h == 0) {
        OS_RestoreInterrupts(mask);
        return 0;
    }
    n = (int *)*h;
    data_02044748[0] = n;
    if (n == 0) data_02044748[4] = 0;
    OS_RestoreInterrupts(mask);
    return h;
}
