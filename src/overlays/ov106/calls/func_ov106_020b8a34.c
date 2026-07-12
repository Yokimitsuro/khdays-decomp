/* Read the +0x60 field of slot param of the second ov106 global object, or 0 if absent. */
extern int data_ov106_020b8b68;
int func_ov106_020b8a34(int param_1) {
    int b = data_ov106_020b8b68;
    if (b == 0) return 0;
    return *(int *)(b + param_1 * 4 + 0x60);
}
