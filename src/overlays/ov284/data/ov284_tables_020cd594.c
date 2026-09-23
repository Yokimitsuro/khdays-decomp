/* ov284 .rodata tables, 0x020cd594-0x020cd5a4.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov284 enemy: raises bit 8 of the +0 flag halfword, installs the handler (020cc0a0): const IdTable data_ov284_020cd594; */
const int data_ov284_020cd594[4] = {
    1, 2, 3, 4,
};
