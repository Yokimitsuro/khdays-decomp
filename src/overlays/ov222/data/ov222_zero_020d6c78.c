/* ov222 .data 0x020d6c78-0x020d6c80: zero fill after the rolling sub-item counter up to the 32-byte
 * end of the overlay's .data. Nothing references it. */
#pragma explicit_zero_data on
char data_ov222_020d6c78[8] = { 0 };
#pragma explicit_zero_data off
