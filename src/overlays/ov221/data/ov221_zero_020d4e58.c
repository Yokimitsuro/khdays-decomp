/* ov221 .data 0x020d4e58-0x020d4e60: zero fill after the rolling sub-item counter up to the 32-byte
 * end of the overlay's .data. Nothing references it. */
#pragma explicit_zero_data on
char data_ov221_020d4e58[8] = { 0 };
#pragma explicit_zero_data off
