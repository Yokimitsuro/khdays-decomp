/* ov225 .data 0x020d5138-0x020d5140: zero fill after the rolling sub-item counter up to the 32-byte
 * end of the overlay's .data. Nothing references it. */
#pragma explicit_zero_data on
char data_ov225_020d5138[8] = { 0 };
#pragma explicit_zero_data off
