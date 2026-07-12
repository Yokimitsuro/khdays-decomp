/* Latch the pending state byte (+0x1c7) into +0x1c6; if it names transition 0 or
 * 1, dispatch the matching handler; then mark +0x1c7 consumed (-1). */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov263_020d311c(void);
extern void func_ov263_020d31dc(void);
void func_ov263_020d3044(int param_1) {
    int child = *(int *)(param_1 + 4);
    signed char v = *(signed char *)(*(int *)child + 0x1c7);
    if (v == -1) return;
    *(signed char *)(*(int *)child + 0x1c6) = v;
    switch (*(signed char *)(*(int *)child + 0x1c6)) {
    case 0:
        func_0203c634(param_1, 1, (void *)&func_ov263_020d311c);
        break;
    case 1:
        func_0203c634(param_1, 1, (void *)&func_ov263_020d31dc);
        break;
    }
    *(signed char *)(*(int *)child + 0x1c7) = -1;
}
