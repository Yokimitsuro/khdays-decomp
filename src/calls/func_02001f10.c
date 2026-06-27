extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern void OSi_InsertLinkToQueue(void *arg0, void *arg1);
extern void func_02001adc();
extern void **data_0204430c[];

void func_02001f10(void *arg0) {
    int mask;
    void *ptr;

    mask = OS_DisableInterrupts();
    ptr = data_0204430c[2][0];
    if (arg0 != 0) {
        ((void **)ptr)[0x1e] = arg0;
        OSi_InsertLinkToQueue(arg0, ptr);
    }
    ((int *)ptr)[0x19] = 0;
    func_02001adc();
    OS_RestoreInterrupts(mask);
}
