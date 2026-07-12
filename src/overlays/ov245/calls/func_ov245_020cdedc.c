/* Set +0x30=0x14000, then dispatch via c634. */
extern int func_0203c634(int, int, void *);
extern int func_ov245_020cdf00(int);
int func_ov245_020cdedc(int param_1) {
    *(int *)(*(int *)(param_1 + 4) + 0x30) = 0x14000;
    return func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov245_020cdf00);
}
