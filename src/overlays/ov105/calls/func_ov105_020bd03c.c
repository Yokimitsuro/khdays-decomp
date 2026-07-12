/* Return 3 when the ov105 status u16 is clear, else 0. */
extern unsigned short data_ov105_020bfa20;
int func_ov105_020bd03c(void) {
    return data_ov105_020bfa20 != 0 ? 0 : 3;
}
