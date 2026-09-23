/* ov219 .rodata tables, 0x020d18a0-0x020d18a8.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov219 enemy (twin of the ov220 constructor, sound 0x136): installs the  (020cfc04): const Kinds data_ov219_020d18a0; */
const u8 data_ov219_020d18a0[4] = {
    2, 3, 4, 0,
};

/* read by Hit handler of the ov219 enemy: records the hit point (+0x30) and parameter (+0x40) in the (020d00e8): const u8 data_ov219_020d18a4[]; */
const u8 data_ov219_020d18a4[4] = {
    0, 1, 2, 3,
};
