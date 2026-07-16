/* func_ov025_02090ffc -- switch the ov025 panel to page param_2 (negative = none).
 * Points obj+0x300 at that page's list (obj+0x304 + page*0xc) and obj+0x78 at its header
 * (obj+page*4+0x7c); then refreshes every node's cached counter byte (+5) from the per-row
 * counters at obj+0x1bf0. */
extern int *NNS_FndGetNextListObject(void *list, int obj);

void func_ov025_02090ffc(int param_1, int param_2) {
    int header;
    if (param_2 < 0) {
        header = 0;
        *(int *)(param_1 + 0x300) = 0;
    } else {
        *(int *)(param_1 + 0x300) = param_2 * 0xc + (param_1 + 0x304);
        header = *(int *)(param_1 + param_2 * 4 + 0x7c);
    }
    *(int *)(param_1 + 0x78) = header;
    {
        int *n = NNS_FndGetNextListObject(*(void **)(param_1 + 0x300), 0);
        if (n != 0) {
            do {
                *(unsigned char *)((int)n + 5) =
                    *(unsigned char *)(param_1 + *(int *)(*n + 0x14) + 0x1bf0);
                n = NNS_FndGetNextListObject(*(void **)(param_1 + 0x300), (int)n);
            } while (n != 0);
        }
    }
}
