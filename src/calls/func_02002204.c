extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern unsigned int data_0204430c[];

unsigned int func_02002204(void) {
    int mask;
    unsigned int old;
    mask = OS_DisableInterrupts();
    old = 0;
    if (data_0204430c[1] != 0) {
        old = data_0204430c[1];
        data_0204430c[1] = old - 1;
    }
    OS_RestoreInterrupts(mask);
    return old;
}
