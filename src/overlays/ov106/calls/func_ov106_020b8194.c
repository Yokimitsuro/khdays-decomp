/* If the ov106 global object exists, store at +0x8ccc. */
extern int data_ov106_020b8b60;
void func_ov106_020b8194(int param_1) {
    int b = data_ov106_020b8b60;
    if (b != 0) *(int *)(b + 0x8ccc) = param_1;
}
