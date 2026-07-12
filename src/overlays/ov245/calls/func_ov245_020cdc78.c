/* Unless the predicate holds, mark state 2 and dispatch via c634. */
extern int func_ov245_020cce48(int);
extern int func_0203c634(int, int, int);
void func_ov245_020cdc78(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (func_ov245_020cce48(*(int *)owner) != 0) return;
    *(signed char *)(*(int *)owner + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
