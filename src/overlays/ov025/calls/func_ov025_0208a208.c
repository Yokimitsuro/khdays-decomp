/* func_ov025_0208a208 -- return the param_2'th node in the list at obj+0x18 counting only the
 * zero-count ones (+0x10 == 0), or 0 if there are fewer than that. */
extern int NNS_FndGetNextListObject(void *list, int obj);

int func_ov025_0208a208(int param_1, int param_2) {
    int idx = 0;
    int n = NNS_FndGetNextListObject((void *)(param_1 + 0x18), 0);
    if (n != 0) {
        do {
            if (*(int *)(n + 0x10) == 0) {
                if (idx == param_2) {
                    break;
                }
                idx = idx + 1;
            }
            n = NNS_FndGetNextListObject((void *)(param_1 + 0x18), n);
        } while (n != 0);
    }
    return n;
}
