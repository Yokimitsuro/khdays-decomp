/* ov004 .rodata tables, 0x0205104c-0x020510a4.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Advance 02030788, then map the current 020315c0 slot to a priority table, storing its inde (0204d368): int data_ov004_0205104c; */
const int data_ov004_0205104c[20] = {
    10, 0, 16, 11, 14, 12, 1, 4,
    5, 6, 7, 9, 13, 15, 17, 18,
    8, 2, 3, 10,
};

/* read by func_ov004_0204fa44 (0204fa44): const Ov004SceneArgs data_ov004_0205109c; */
const int data_ov004_0205109c[2] = {
    1, 1,
};
