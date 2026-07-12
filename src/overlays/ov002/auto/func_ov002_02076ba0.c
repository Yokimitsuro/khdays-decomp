/* Invoke the optional callback at (*(param_1+8))+0x38 with the two incoming args. */
void func_ov002_02076ba0(int param_1, int param_2) {
    void (*cb)(int, int) = *(void (**)(int, int))(*(int *)(param_1 + 8) + 0x38);
    if (cb != 0) cb(param_1, param_2);
}
