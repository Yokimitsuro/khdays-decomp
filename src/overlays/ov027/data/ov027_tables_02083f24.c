/* ov027 .data tables, 0x02083f24-0x02083f54.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

int data_ov027_02083f24[1] = {
    724992,
};

int data_ov027_02083f28[11] = {
    491520, 724992,
    557056, 724992,
    622592, 659456,
    557056, 659456,
    622592, 0,
    0,
};
