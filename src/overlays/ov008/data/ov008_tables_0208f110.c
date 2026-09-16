/* ov008 .rodata tables, 0x0208f110-0x0208f14c.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_0208f110: func_ov008_0205dbcc
 *   data_ov008_0208f118: func_ov008_0205cde8
 *   data_ov008_0208f124: func_ov008_02063790
 *   data_ov008_0208f130: func_ov008_0205d56c
 *   data_ov008_0208f13c: func_ov008_02062d00
 */

typedef unsigned char u8;
typedef unsigned short u16;

const int data_ov008_0208f110[2] = {
    62, 63,
};

const int data_ov008_0208f118[3] = {
    16, 17, 18,
};

const int data_ov008_0208f124[3] = {
    6, 5, 4,
};

const int data_ov008_0208f130[3] = {
    4, 3, 0,
};

const int data_ov008_0208f13c[4] = {
    72, 73, 70, 71,
};
