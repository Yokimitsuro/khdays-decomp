/* Copy the queued sub-state +0x1c7 into +0x1c6 (bail if -1) and dispatch the matching handler. */
extern int func_0203c634(int, int, void *);
extern int func_ov254_020d47b0(int);
extern int func_ov254_020d482c(int);
extern int func_ov254_020d4cb4(int);
void func_ov254_020d46e4(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int sub = *(signed char *)(*(int *)owner + 0x1c7);
    if (sub == -1) return;
    *(signed char *)(*(int *)owner + 0x1c6) = sub;
    switch (*(signed char *)(*(int *)owner + 0x1c6)) {
    case 0: func_0203c634(param_1, 1, (void *)&func_ov254_020d47b0); break;
    case 1: func_0203c634(param_1, 1, (void *)&func_ov254_020d482c); break;
    case 2: func_0203c634(param_1, 1, (void *)&func_ov254_020d4cb4); break;
    }
    *(signed char *)(*(int *)owner + 0x1c7) = -1;
}
