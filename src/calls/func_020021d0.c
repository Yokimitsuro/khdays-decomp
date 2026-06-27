extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern unsigned int data_0204430c[];

unsigned int func_020021d0(void) {
    int mask;
    unsigned int old;
    mask = OS_DisableInterrupts();
    if (data_0204430c[1] < 0xFFFFFFFFu) {
        old = data_0204430c[1];
        data_0204430c[1] = old + 1;
    }
    OS_RestoreInterrupts(mask);
    return old;
}
