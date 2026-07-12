/* Unless either sibling is busy, mark state 0 and dispatch via c634. */
extern int func_0203c634(int, int, int);
void func_ov254_020d58d4(int param_1) {
    int obj = *(int *)(*(int *)(param_1 + 4));
    if (*(unsigned char *)(*(int *)(obj + 0x384) + 0xad) != 0 ||
        *(unsigned char *)(*(int *)(obj + 0x388) + 0xad) != 0) return;
    *(signed char *)(obj + 0x1c7) = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
