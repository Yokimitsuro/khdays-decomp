/* Clear the linked node's +0x4e0, latch the queued sub-state +0x1c7 into +0x1c6, dispatch the
 * matching handler, then reset +0x1c7 to -1. */
extern int func_0203c634(int, int, void *);
extern int func_ov254_020d2564(int);
extern int func_ov254_020d2608(int);
extern int func_ov254_020d2980(int);
void func_ov254_020d24bc(int param_1) {
    int owner = *(int *)(param_1 + 4);
    *(int *)(*(int *)(*(int *)owner + 0x390) + 0x4e0) = 0;
    int sub = *(signed char *)(*(int *)owner + 0x1c7);
    if (sub != -1) {
        *(signed char *)(*(int *)owner + 0x1c6) = sub;
        switch (*(signed char *)(*(int *)owner + 0x1c6)) {
        case 0: func_0203c634(param_1, 1, (void *)&func_ov254_020d2564); break;
        case 1: func_0203c634(param_1, 1, (void *)&func_ov254_020d2608); break;
        case 2: func_0203c634(param_1, 1, (void *)&func_ov254_020d2980); break;
        }
    }
    *(signed char *)(*(int *)owner + 0x1c7) = -1;
}
