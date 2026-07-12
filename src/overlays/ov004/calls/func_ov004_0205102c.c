/* Read the word at +0x5550 of the ov004 global object, or 1 if absent. */
extern int data_ov004_02051384;
int func_ov004_0205102c(void) {
    if (data_ov004_02051384 == 0) return 1;
    return *(int *)(data_ov004_02051384 + 0x5550);
}
