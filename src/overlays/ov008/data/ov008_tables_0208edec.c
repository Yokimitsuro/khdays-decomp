/* ov008 .rodata tables, 0x0208edec-0x0208ee84.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_0208edec: func_ov008_0205ab5c
 *   data_ov008_0208edfc: func_ov008_0205ab5c
 *   data_ov008_0208ee0c: func_ov008_0205af54
 *   data_ov008_0208ee34: func_ov008_0205af54
 *   data_ov008_0208ee5c: func_ov008_0205af54
 */

typedef unsigned char u8;
typedef unsigned short u16;

const int data_ov008_0208edec[4] = {
    0, 2, 0, 0,
};

const int data_ov008_0208edfc[4] = {
    0, 1, 0, 0,
};

const int data_ov008_0208ee0c[10] = {
    22, 5, 15, 2, 178, 15, 0, 5,
    0, 32,
};

const int data_ov008_0208ee34[10] = {
    22, 24, 8, 2, 208, 15, 0, 5,
    0, 32,
};

const int data_ov008_0208ee5c[10] = {
    0, 14, 18, 2, 142, 15, 0, 5,
    0, 32,
};
