/* Invoke the optional callback at (*(param_1+8))+8 with the three incoming args. */
void func_ov002_02076bbc(int param_1, int param_2, int param_3) {
    void (*cb)(int, int, int) = *(void (**)(int, int, int))(*(int *)(param_1 + 8) + 8);
    if (cb != 0) cb(param_1, param_2, param_3);
}
