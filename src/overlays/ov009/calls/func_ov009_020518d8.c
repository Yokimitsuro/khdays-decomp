/* Notify func_02032388, then set status bit 2 (mask 4) at param_1+0x4a7c. */
extern void func_02032388(int obj);
void func_ov009_020518d8(int param_1) {
    func_02032388(param_1);
    *(int *)(param_1 + 0x4a7c) |= 4;
}
