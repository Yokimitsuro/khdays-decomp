/* ov026 .data tables, 0x0209130c-0x02091340.
 *
 * 6 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

u16 data_ov026_0209130c[4] = { '%', 'd', 0, 0 };

u16 data_ov026_02091314[4] = { '%', '3', 'd', 0 };

u16 data_ov026_0209131c[4] = { '?', '?', 0, 0 };

u16 data_ov026_02091324[10] = { '?', '?', '?', '?', '?', '?', '?', '?', 0, 0 };

int data_ov026_02091338[1] = {
    91,
};

int data_ov026_0209133c[1] = {
    93,
};
