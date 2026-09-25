/* ov005 .data tables, 0x0205b7a8-0x0205b7cc.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* Shift-JIS text "dango daikazoku", a placeholder title. */
char data_ov005_0205b7a8[16] = "\x82\xbe\x82\xf1\x82\xb2\x91\xe5\x89\xc6\x91\xb0";

/* Shift-JIS text "yasashii an-dango". */
char data_ov005_0205b7b8[20] = "\x82\xe2\x82\xb3\x82\xb5\x82\xa2\x82\xa0\x82\xf1\x82\xbe\x82\xf1\x82\xb2";
