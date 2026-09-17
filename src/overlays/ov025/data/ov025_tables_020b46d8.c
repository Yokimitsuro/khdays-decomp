/* ov025 .rodata tables, 0x020b46d8-0x020b4968.
 *
 * 15 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes, followed by the four character tag "KPTS" (two bytes of
 * padding) of the report detail byte tables data_ov025_020b4960 .. 020b4968,
 * which are indexed by the mode; the tag shares this unit because it sits
 * at a 2-byte offset and mwcc keeps byte objects packed inside one section.
 *
 * Readers:
 *   data_ov025_020b46d8: func_ov025_020ab7b0
 *   data_ov025_020b46e8: func_ov025_020ad3bc
 *   data_ov025_020b46fc: func_ov025_020ac994
 *   data_ov025_020b4724: func_ov025_020ac994
 *   data_ov025_020b474c: func_ov025_020ac994
 *   data_ov025_020b4774: func_ov025_020ac994
 *   data_ov025_020b479c: func_ov025_020ac994
 *   data_ov025_020b47c4: func_ov025_020ac994
 *   data_ov025_020b47ec: func_ov025_020ab7b0
 *   data_ov025_020b481c: func_ov025_020ae28c
 *   data_ov025_020b4844: func_ov025_020af6a0
 *   data_ov025_020b495c: func_ov025_020afdd4, func_ov025_020afef4
 *   data_ov025_020b495d: (no C reader yet)
 *   data_ov025_020b4960: func_ov025_020afdd4, func_ov025_020afef4
 *   data_ov025_020b4961: (no C reader yet)
 *   data_ov025_020b4962: (no C reader yet)
 */

typedef unsigned char u8;
typedef unsigned short u16;

const int data_ov025_020b46d8[4] = {
    47, 44, 45, 46,
};

const int data_ov025_020b46e8[5] = {
    1, 2, 11, 12, 13,
};

const int data_ov025_020b46fc[10] = {
    1, 24, 2, 2, 352, 8, 0, 20,
    0, 32,
};

const int data_ov025_020b4724[10] = {
    1, 21, 5, 2, 352, 8, 0, 20,
    0, 32,
};

const int data_ov025_020b474c[10] = {
    0, 2, 25, 30, 1, 0, 0, 22,
    0, 32,
};

const int data_ov025_020b4774[10] = {
    22, 0, 32, 2, 352, 8, 0, 20,
    0, 32,
};

const int data_ov025_020b479c[10] = {
    3, 5, 20, 2, 352, 8, 0, 20,
    0, 32,
};

const int data_ov025_020b47c4[10] = {
    1, 5, 18, 2, 352, 8, 0, 20,
    0, 32,
};

const int data_ov025_020b47ec[12] = {
    1100, 1105, 1104, 1101, 1103, 1106, 1100, 1100,
    1107, 1102, 1100, 1100,
};

const int data_ov025_020b481c[10] = {
    0, 10, 17, 2, 288, 8, 0, 22,
    0, 32,
};

const int data_ov025_020b4844[70] = {
    0, 2, 22, 3, 1, 15, 0, 23,
    0, 32, 0, 25, 6, 3, 67, 15,
    0, 23, 0, 32, 3, 2, 28, 4,
    85, 15, 0, 23, 0, 32, 20, 2,
    28, 3, 197, 15, 0, 23, 0, 32,
    8, 18, 13, 4, 197, 15, 0, 23,
    0, 32, 13, 18, 13, 4, 249, 15,
    0, 23, 0, 32, 19, 18, 13, 4,
    301, 15, 0, 23, 0, 32,
};

const u8 data_ov025_020b495c[1] = {
    3,
};

const u8 data_ov025_020b495d[3] = {
    4, 4, 6,
};

const u8 data_ov025_020b4960[1] = {
    72,
};

const u8 data_ov025_020b4961[1] = {
    76,
};

const char data_ov025_020b4962[6] = "KPTS";
