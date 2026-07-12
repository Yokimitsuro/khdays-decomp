/* Latch the queued sub-state into +0x1c6, reset +0x1c7, and dispatch the matching handler. */
extern int func_0203c634(int, int, void *);
extern int func_ov255_020d1d00(int);
extern int func_ov255_020d1df8(int);
void func_ov255_020d1c5c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int sub = *(signed char *)(*(int *)owner + 0x1c7);
    if (sub == -1) return;
    *(signed char *)(*(int *)owner + 0x1c6) = sub;
    *(signed char *)(*(int *)owner + 0x1c7) = -1;
    switch (*(signed char *)(*(int *)owner + 0x1c6)) {
    case 0: func_0203c634(param_1, 1, (void *)&func_ov255_020d1d00); break;
    case 1: func_0203c634(param_1, 1, (void *)&func_ov255_020d1df8); break;
    }
}
