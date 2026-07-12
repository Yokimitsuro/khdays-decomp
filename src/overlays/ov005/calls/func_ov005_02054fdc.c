/* Read the word at +0x4c34 of the ov005 global object. */
extern int data_ov005_0205b80c;
int func_ov005_02054fdc(void) {
    return *(int *)(data_ov005_0205b80c + 0x4c34);
}
