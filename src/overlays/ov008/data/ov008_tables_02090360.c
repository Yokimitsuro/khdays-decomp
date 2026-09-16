/* ov008 .data tables, 0x02090360-0x02090380.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_02090360: func_ov008_0205f050
 *   data_ov008_02090370: func_ov008_0205f050
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov008_02090360[16] = {
    196, 36, 196, 36, 196, 36, 196, 36, 109, 102, 232, 85, 70, 61, 228, 44,
};

u8 data_ov008_02090370[16] = {
    75, 12, 105, 16, 104, 16, 135, 20, 152, 24, 117, 20, 114, 16, 77, 12,
};
