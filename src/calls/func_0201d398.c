extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern void NNS_FndAppendListObject(void *list, void *object);
extern int data_0204ad98[];

void func_0201d398(void *object) {
    int mask;
    mask = OS_DisableInterrupts();
    NNS_FndAppendListObject(data_0204ad98, object);
    OS_RestoreInterrupts(mask);
}
