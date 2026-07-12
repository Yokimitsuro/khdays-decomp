/* Clear bit 0 and set bit 1 of the word pointed to by the ov026 global pointer. */
extern int data_ov026_02091360;
void func_ov026_02082af0(void) {
    *(int *)data_ov026_02091360 = (*(int *)data_ov026_02091360 & ~1) | 2;
}
