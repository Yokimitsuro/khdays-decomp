/* ov009 .rodata tables, 0x02055f6c-0x02055f88.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Flush the dirty menu cell buffers to VRAM. For each of the 7 cell slots whose bit is set (0204db88): int  data_ov009_02055f6c[]; */
const int data_ov009_02055f6c[7] = {
    9, 10, 11, 24, 25, 26, 27,
};
