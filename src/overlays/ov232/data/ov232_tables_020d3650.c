/* ov232 .rodata tables, 0x020d3650-0x020d3670.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov231 enemy (x5 with ov232/ov263/ov265/ov280). Installs the handlers (+ (020cfc08): KindTable data_ov232_020d3650; */
const int data_ov232_020d3650[8] = {
    18, 19, 20, 21, 22, 23, 24, 25,
};
