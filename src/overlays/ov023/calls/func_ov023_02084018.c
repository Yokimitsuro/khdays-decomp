extern int data_ov023_0208a784;
/* Read the far field at +0x875e8 of the ov023 table base. */
int func_ov023_02084018(void) {
    return *(int *)((&data_ov023_0208a784)[1] + 0x875e8);
}
