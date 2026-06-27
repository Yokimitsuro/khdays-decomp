extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern int *data_02044748[];

int func_02008aa0(void) {
    int mask;
    int count;
    int *p;
    mask = OS_DisableInterrupts();
    count = 0;
    p = data_02044748[2];
    if (p != 0) {
        do {
            p = (int *)*p;
            count++;
        } while (p != 0);
    }
    OS_RestoreInterrupts(mask);
    return count;
}
