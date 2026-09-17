/* ov025 .data tables, 0x020b52ec-0x020b52fc.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov025_020b52ec: func_ov025_020a2844
 *   data_ov025_020b52f8: func_ov025_020a2b00
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov025_020b52ec[12] = {
    37, 0, 100, 0, 47, 0, 37, 0, 100, 0, 0, 0,
};

u8 data_ov025_020b52f8[4] = {
    252, 48, 0, 0,
};
