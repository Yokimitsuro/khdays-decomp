extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern int data_02044748[];

int func_020089e8(void) {
    int mask;
    int result;
    mask = OS_DisableInterrupts();
    if (data_02044748[2] == 0) {
        result = data_02044748[1];
    } else {
        result = data_02044748[8];
    }
    OS_RestoreInterrupts(mask);
    return result;
}
