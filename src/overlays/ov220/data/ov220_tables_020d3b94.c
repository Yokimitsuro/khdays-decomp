/* ov220 .rodata tables, 0x020d3b94-0x020d3b9c.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov220 enemy (and its byte-identical twin ov220): installs the handlers (020d1a24): const Kinds data_ov220_020d3b94; */
const u8 data_ov220_020d3b94[4] = {
    2, 3, 4, 0,
};

/* read by Hit handler of the ov220 enemy (variant of the ov219 handler): ignores hits while bit 0 of (020d1f08): const u8 data_ov220_020d3b98[]; */
const u8 data_ov220_020d3b98[4] = {
    0, 1, 2, 3,
};
