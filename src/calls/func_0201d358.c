extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern void *NNS_FndGetNextListObject(void *list, void *object);
extern void NNS_FndRemoveListObject(void *list, void *object);
extern int data_0204ad98[];

void *func_0201d358(void) {
    int mask;
    void *p;
    mask = OS_DisableInterrupts();
    p = NNS_FndGetNextListObject(data_0204ad98, 0);
    if (p) {
        NNS_FndRemoveListObject(data_0204ad98, p);
    }
    OS_RestoreInterrupts(mask);
    return p;
}
