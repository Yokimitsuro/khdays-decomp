/* Read the word at +0x4b78 of the ov005 global object. */
extern int data_ov005_0205b810;
int func_ov005_02057ab4(void) {
    return *(int *)(data_ov005_0205b810 + 0x4b78);
}
