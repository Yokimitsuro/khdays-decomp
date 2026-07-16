/* func_ov008_0206e05c -- find the node in the list at obj+0x1cc whose (+8, +0) pair matches
 * (param_2, param_3), also reporting its ordinal through param_4 when given. */
extern int *NNS_FndGetNextListObject(void *list, int obj);

int *func_ov008_0206e05c(int param_1, int param_2, int param_3, int *param_4) {
    int idx = 0;
    int *n;
    for (n = NNS_FndGetNextListObject((void *)(param_1 + 0x1cc), 0); n != 0;
         n = NNS_FndGetNextListObject((void *)(param_1 + 0x1cc), (int)n)) {
        if (n[2] == param_2 && *n == param_3) {
            break;
        }
        idx = idx + 1;
    }
    if (param_4 != 0) {
        *param_4 = idx;
    }
    return n;
}
