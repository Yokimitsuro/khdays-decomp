/* func_ov004_0204d328 -- return the first node in the list at obj+0x18 whose count (+0x10) is
 * positive, or 0 if none. */
extern int NNS_FndGetNextListObject(void *list, int obj);

int func_ov004_0204d328(int param_1) {
    int n = NNS_FndGetNextListObject((void *)(param_1 + 0x18), 0);
    if (n != 0) {
        do {
            if (*(int *)(n + 0x10) > 0) {
                break;
            }
            n = NNS_FndGetNextListObject((void *)(param_1 + 0x18), n);
        } while (n != 0);
    }
    return n;
}
