extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern unsigned int data_02044748[];

int func_02008a14(unsigned int target) {
    int mask;
    int result;
    unsigned int current;
    mask = OS_DisableInterrupts();
    current = data_02044748[1];
    if (target > current) {
        if ((target - current) < 0x80000000u) {
            result = 0;
        } else {
            result = 1;
        }
    } else {
        if ((current - target) < 0x80000000u) {
            result = 1;
        } else {
            result = 0;
        }
    }
    OS_RestoreInterrupts(mask);
    return result;
}
