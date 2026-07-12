/* Kick func_02032388 for param_1, then set status bit 2 (0x4) at param_1+0x4a7c. */
extern void func_02032388(int obj);

void func_ov008_02054744(int param_1) {
    func_02032388(param_1);
    *(int *)(param_1 + 0x4a7c) |= 4;
}
