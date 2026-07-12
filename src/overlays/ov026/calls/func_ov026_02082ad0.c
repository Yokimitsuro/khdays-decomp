/* Report whether bit 3 of the word pointed to by the ov026 global pointer is clear. */
extern int data_ov026_02091360;
int func_ov026_02082ad0(void) {
    return (*(int *)data_ov026_02091360 & 8) == 0;
}
