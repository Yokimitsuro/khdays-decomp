/* Latch the pending state byte (+0x1c7) into +0x1c6; if valid and it names
 * transition 0 or 1, dispatch the matching handler; then mark +0x1c7 consumed. */
extern int func_0203c634(int a, int b, void *handler);
extern void func_ov260_020d277c(void);
extern void func_ov260_020d27ec(void);
void func_ov260_020d26e4(int param_1) {
    int child = *(int *)(param_1 + 4);
    signed char v = *(signed char *)(*(int *)child + 0x1c7);
    if (v != -1) {
        *(signed char *)(*(int *)child + 0x1c6) = v;
        switch (*(signed char *)(*(int *)child + 0x1c6)) {
        case 0:
            func_0203c634(param_1, 1, (void *)&func_ov260_020d277c);
            break;
        case 1:
            func_0203c634(param_1, 1, (void *)&func_ov260_020d27ec);
            break;
        }
    }
    *(signed char *)(*(int *)child + 0x1c7) = -1;
}
