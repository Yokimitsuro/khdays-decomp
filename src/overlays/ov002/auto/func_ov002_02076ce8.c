/* Invoke the optional callback at (*(param_1+8))+0x30 with the two incoming args. */
void func_ov002_02076ce8(int param_1, int param_2) {
    void (*cb)(int, int) = *(void (**)(int, int))(*(int *)(param_1 + 8) + 0x30);
    if (cb != 0) cb(param_1, param_2);
}
