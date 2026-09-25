/* ov029 .rodata tables, 0x020b30b0-0x020b31f0.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by * Ov029_AcquireOverlaySlot -- overlay slot allocator.  THUMB. (020b2ee0): OverlayGroup   data_ov029_020b30b0[]; */
const int data_ov029_020b30b0[20][4] = {
    { 30, -1, -1, -1 },
    { 31, 50, 70, 88 },
    { 32, 52, 72, -1 },
    { 33, 51, 71, 89 },
    { 34, 53, 73, 90 },
    { 35, 54, 74, 91 },
    { 36, 55, 75, 92 },
    { 37, 56, 76, 93 },
    { 38, 57, 77, 94 },
    { 39, 58, 78, 95 },
    { 40, 59, 79, 96 },
    { 41, 60, 80, 97 },
    { 42, 61, 81, 98 },
    { 43, 62, -1, -1 },
    { 44, 63, 82, 99 },
    { 45, 64, 83, 100 },
    { 46, 65, 84, 101 },
    { 47, 66, 85, 102 },
    { 48, 67, 86, 103 },
    { 49, 68, 87, 104 },
};
