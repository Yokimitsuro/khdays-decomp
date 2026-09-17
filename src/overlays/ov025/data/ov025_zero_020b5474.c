/* ov025 empty reward text data_ov025_020b5474, 0x020b5474-0x020b5478 (.data): the
 * u16 string shown by 020abdd8 when a mission has no reward.  Kept in .data with
 * explicit_zero_data so it stays where the ROM has it.
 */

typedef unsigned short u16;

#pragma explicit_zero_data on
u16 data_ov025_020b5474[2] = { 0, 0 };
#pragma explicit_zero_data off
