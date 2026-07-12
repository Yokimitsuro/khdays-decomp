/* Clear bit 1 of the object's +0x5c flags, then dispatch via c634. */
extern int func_0203c634(int, int, void *);
extern int func_ov107_020c08ac(int);
int func_ov107_020c0868(int param_1) {
    int obj = *(int *)(*(int *)(param_1 + 4));
    *(int *)(obj + 0x5c) &= ~2;
    return func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov107_020c08ac);
}
