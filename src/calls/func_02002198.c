extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern int data_0204430c[];

int func_02002198(int arg0) {
    int mask;
    int old;
    mask = OS_DisableInterrupts();
    old = data_0204430c[0xc];
    data_0204430c[0xc] = arg0;
    OS_RestoreInterrupts(mask);
    return old;
}
