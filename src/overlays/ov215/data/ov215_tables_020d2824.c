/* ov215 .rodata tables, 0x020d2824-0x020d2868.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov215_020cfe3c (020cfe3c): KindTable data_ov215_020d2824; */
const int data_ov215_020d2824[5] = {
    0, 11, 12, 13, 15,
};

/* read by func_ov215_020d0620 (020d0620): int data_ov215_020d2838[]; */
const int data_ov215_020d2838[9] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9,
};

/* read by Applies one hit event to the actor (Ghidra: Ov215_ApplyHitEvent). (020d06f4): u8 data_ov215_020d285c[]; */
const u8 data_ov215_020d285c[12] = {
    2, 3, 0, 1, 248, 7, 0, 0, 102, 62, 0, 0,
};
