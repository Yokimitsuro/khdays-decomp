/* ov004 .data tables, 0x0205136c-0x02051380.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

u16 data_ov004_0205136c[10] = { 0xff5e /* fullwidth ~ */, '%', 'l', 's', 0xff5e /* fullwidth ~ */, 0, 0, 0, 0, 0 };
