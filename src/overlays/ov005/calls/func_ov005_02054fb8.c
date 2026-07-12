/* Report whether +0x4bf0 of the ov005 global object equals 6. */
extern int data_ov005_0205b80c;
int func_ov005_02054fb8(void) {
    return *(int *)(data_ov005_0205b80c + 0x4bf0) == 6;
}
