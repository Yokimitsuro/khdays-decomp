/* Report whether bit 4 of the u16 pointed to by the ov023 global pointer is set. */
extern int data_ov023_0208a780;
int func_ov023_02082c9c(void) {
    return (*(unsigned short *)data_ov023_0208a780 & 0x10) > 0;
}
