/* Read bit 2 of the word pointed to by the ov026 global pointer. */
extern int data_ov026_02091360;
int func_ov026_02082b2c(void) {
    return *(int *)data_ov026_02091360 & 4;
}
