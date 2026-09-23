/* ov011 .rodata tables, 0x0205dca0-0x0205e130.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov011_0205cda0 (0205cda0): void data_ov011_0205dca0(void); */
const u8 data_ov011_0205dca0[48] = {
    3, 0, 0, 0, 83, 0, 81, 0, 69, 0, 88, 0, 1, 0, 0, 0,
    68, 0, 83, 0, 78, 0, 49, 0, 2, 0, 0, 0, 68, 0, 83, 0,
    78, 0, 50, 0, 0, 0, 0, 0, 72, 0, 65, 0, 78, 0, 68, 0,
};

/* read by Ov011_EmitSlotGfx (348 B, ARM, 8 relocs). Direct dependency of (0205d508): Ov011GfxTemplate data_ov011_0205dcd0; */
const int data_ov011_0205dcd0[16] = {
    17, 6, 10, 2, 17, 7, 11, 3,
    33, 22, 26, 2, 33, 23, 27, 3,
};

/* read by switch the scene into mode 2 and rebuild its display for it. (0205c074): const u8 data_ov011_0205dd10[]; */
const int data_ov011_0205dd10[24] = {
    97, 0, 0, 0, 19, 60, 0, 0,
    80, 177, 0, 0, 35, 90, 0, 0,
    80, 90, 0, 0, 80, 30, 0, 0,
};

/* read by Ov011_Mode2Teardown -- title tick handler for scene mode 2: reset the layout (0205c190): const int data_ov011_0205dd70; */
const int data_ov011_0205dd70[76] = {
    80, 20, 0, 0, 128, 0, 0, 0,
    80, 4, 0, 0, 99, 0, 0, 0,
    17, 60, 0, 0, 80, 60, 0, 0,
    18, 60, 0, 0, 80, 165, 0, 0,
    35, 90, 0, 0, 80, 177, 0, 0,
    144, 0, 0, 0, 99, 0, 0, 1,
    19, 60, 0, 0, 80, 60, 0, 0,
    80, 90, 0, 0, 160, 0, 0, 0,
    128, 120, 1, 0, 35, 60, 0, 0,
    80, 120, 0, 0,
};

/* read by point the scene at its 0x29-entry table and reset the cursor. (0205bddc): const u8 data_ov011_0205dea0[]; */
const int data_ov011_0205dea0[164] = {
    80, 98, 0, 0, 99, 0, 0, 0,
    19, 30, 0, 0, 80, 120, 0, 0,
    99, 0, 0, 1, 67, 30, 0, 0,
    80, 15, 0, 0, 51, 30, 0, 0,
    80, 145, 0, 0, 99, 0, 0, 2,
    67, 30, 0, 0, 80, 15, 0, 0,
    51, 30, 0, 0, 80, 145, 0, 0,
    99, 0, 0, 3, 67, 30, 0, 0,
    80, 15, 0, 0, 51, 30, 0, 0,
    80, 150, 0, 0, 99, 0, 0, 4,
    67, 30, 0, 0, 80, 15, 0, 0,
    51, 30, 0, 0, 80, 150, 0, 0,
    99, 0, 0, 5, 67, 30, 0, 0,
    80, 15, 0, 0, 51, 30, 0, 0,
    80, 120, 0, 0, 99, 0, 0, 6,
    67, 30, 0, 0, 80, 15, 0, 0,
    51, 30, 0, 0, 80, 105, 0, 0,
    99, 0, 0, 7, 67, 30, 0, 0,
    80, 37, 0, 0, 51, 30, 0, 0,
    80, 152, 0, 0, 67, 90, 17, 0,
    80, 90, 0, 0,
};
