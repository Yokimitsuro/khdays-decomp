/* Clear bit 0 and set bit 1 of the +0x1c flags of the ov027 object. */
extern int data_ov027_02084360;
void func_ov027_02082b08(void) {
    *(int *)((&data_ov027_02084360)[1] + 0x1c) &= ~1;
    *(int *)((&data_ov027_02084360)[1] + 0x1c) |= 2;
}
