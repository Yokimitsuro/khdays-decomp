/* Latch the queued sub-state +0x1c7 into +0x1c6 (bail if -1), clear bit4 of +0x1ae, dispatch the
 * matching handler, then reset +0x1c7 to -1. */
extern int func_0203c634(int, int, void *);
extern int func_ov245_020d1798(int);
extern int func_ov245_020d1858(int);
extern int func_ov245_020d1bcc(int);
void func_ov245_020d16d8(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int sub = *(signed char *)(*(int *)owner + 0x1c7);
    if (sub == -1) return;
    *(signed char *)(*(int *)owner + 0x1c6) = sub;
    *(unsigned short *)(*(int *)owner + 0x1ae) &= ~0x10;
    switch (*(signed char *)(*(int *)owner + 0x1c6)) {
    case 0: func_0203c634(param_1, 1, (void *)&func_ov245_020d1798); break;
    case 1: func_0203c634(param_1, 1, (void *)&func_ov245_020d1858); break;
    case 2: func_0203c634(param_1, 1, (void *)&func_ov245_020d1bcc); break;
    }
    *(signed char *)(*(int *)owner + 0x1c7) = -1;
}
