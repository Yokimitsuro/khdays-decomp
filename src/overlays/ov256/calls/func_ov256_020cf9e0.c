/* Advance the +0x4c timer; unless busy, set state from +0x74 and dispatch via c634. */
extern int func_0203c634(int, int, void *);
void func_ov256_020cf9e0(int param_1) {
    int a = *(int *)param_1;
    int owner = *(int *)(param_1 + 4);
    *(int *)(owner + 0x4c) += *(int *)(a + 0x2c);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)owner + 0x1c7) = *(int *)(owner + 0x74) + 2;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
}
