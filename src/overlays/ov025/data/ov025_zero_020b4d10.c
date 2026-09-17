/* ov025 zero words in .data: data_ov025_020b4d10 (an empty byte string passed by
 * 0208d454 / 0208e000), data_ov025_020b536c and data_ov025_020b5474 (the empty reward
 * texts of 020a54c8 / 020abdd8).  Kept in .data with explicit_zero_data so they stay
 * where the ROM has them instead of moving to .bss.
 */

typedef unsigned char u8;
typedef unsigned short u16;

#pragma explicit_zero_data on
u8 data_ov025_020b4d10[4] = { 0, 0, 0, 0 };
#pragma explicit_zero_data off
