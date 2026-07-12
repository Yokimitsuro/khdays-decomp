/* If the ov005 global object exists, store a word at +0x4c2c. */
extern int data_ov005_0205b80c;
void func_ov005_02054f9c(int param_1) {
    if (data_ov005_0205b80c != 0) *(int *)(data_ov005_0205b80c + 0x4c2c) = param_1;
}
