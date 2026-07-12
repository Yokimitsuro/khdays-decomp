/* Latch the queued sub-state +0x1c7 into +0x1c6 (bail if -1), release the +0x2c partner via
 * 020ad8e0, dispatch the matching handler, then reset +0x1c7 to -1. */
extern int func_ov022_020ad8e0(int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov160_020cefd8(int);
extern int func_ov160_020cf0c0(int);
void func_ov160_020cef20(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int sub = *(signed char *)(*(int *)owner + 0x1c7);
    if (sub == -1) return;
    *(signed char *)(*(int *)owner + 0x1c6) = sub;
    if (*(int *)(owner + 0x2c) != 0) {
        func_ov022_020ad8e0(*(int *)(owner + 0x2c), 0);
        *(int *)(owner + 0x2c) = 0;
    }
    switch (*(signed char *)(*(int *)owner + 0x1c6)) {
    case 0: func_0203c634(param_1, 1, (void *)&func_ov160_020cefd8); break;
    case 1: func_0203c634(param_1, 1, (void *)&func_ov160_020cf0c0); break;
    }
    *(signed char *)(*(int *)owner + 0x1c7) = -1;
}
