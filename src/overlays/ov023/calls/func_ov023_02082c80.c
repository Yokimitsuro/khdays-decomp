/* Set bit 4 of the u16 pointed to by the ov023 global pointer. */
extern int data_ov023_0208a780;
void func_ov023_02082c80(void) {
    *(unsigned short *)data_ov023_0208a780 |= 0x10;
}
