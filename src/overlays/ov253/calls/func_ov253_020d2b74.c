/* Unless the predicate holds for the +0x20 value, dispatch via c634. */
extern int func_ov253_020d27f8(int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov253_020d2aec(int);
void func_ov253_020d2b74(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (func_ov253_020d27f8(*(int *)owner, *(short *)(owner + 0x20)) != 0) return;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov253_020d2aec);
}
