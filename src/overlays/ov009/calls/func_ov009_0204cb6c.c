/* Store a word at +0x95cc of the second ov009 global object. */
extern int data_ov009_020563e4;
void func_ov009_0204cb6c(int param_1) {
    *(int *)((&data_ov009_020563e4)[1] + 0x95cc) = param_1;
}
