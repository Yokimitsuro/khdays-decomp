/* Set bit 2 of the +0x1c flags of the ov027 object. */
extern int data_ov027_02084360;
void func_ov027_02082b24(void) {
    *(int *)((&data_ov027_02084360)[1] + 0x1c) |= 4;
}
