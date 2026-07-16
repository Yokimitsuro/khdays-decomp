/* func_ov025_020922fc -- find the grid hit entry matching (page, col, row) in the list at
 * obj+0x1e7c (keys at +10, +0x10, +0x12). Returns 0 when nothing matches. */
extern int NNS_FndGetNextListObject(void *list, int obj);

int func_ov025_020922fc(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4) {
    int n;
    for (n = NNS_FndGetNextListObject((void *)(param_1 + 0x1e7c), 0); n != 0;
         n = NNS_FndGetNextListObject((void *)(param_1 + 0x1e7c), n)) {
        if (*(unsigned short *)(n + 10) == param_2 &&
            *(unsigned short *)(n + 0x10) == param_3 &&
            *(unsigned short *)(n + 0x12) == param_4) {
            break;
        }
    }
    return n;
}
