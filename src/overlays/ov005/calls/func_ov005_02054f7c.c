/* If the ov005 global object exists, set +0x4c38 to 1. */
extern int data_ov005_0205b80c;
void func_ov005_02054f7c(void) {
    if (data_ov005_0205b80c != 0) *(int *)(data_ov005_0205b80c + 0x4c38) = 1;
}
