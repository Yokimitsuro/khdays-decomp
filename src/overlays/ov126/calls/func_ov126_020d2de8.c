/* Clear the owner's +0x30 field, then dispatch via c634. */
extern int func_0203c634(int, int, void *);
extern int func_ov126_020d2e0c(int);
int func_ov126_020d2de8(int param_1) {
    *(int *)(*(int *)(param_1 + 4) + 0x30) = 0;
    return func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov126_020d2e0c);
}
