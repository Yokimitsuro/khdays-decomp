/* Set the word at +0x4c5c of the ov005 global object to 1. */
extern int data_ov005_0205b810;
void func_ov005_02057a18(void) {
    *(int *)(data_ov005_0205b810 + 0x4c5c) = 1;
}
