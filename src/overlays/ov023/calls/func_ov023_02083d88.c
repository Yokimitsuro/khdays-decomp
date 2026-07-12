/* Report bit 2 of the far flags at +0x8757c of the ov023 table base. */
extern int data_ov023_0208a784;
struct bf3 { unsigned int b0:1, b1:1, b2:1; };
int func_ov023_02083d88(void) {
    return ((struct bf3 *)((&data_ov023_0208a784)[1] + 0x8757c))->b2;
}
