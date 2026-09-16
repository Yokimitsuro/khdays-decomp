/* ov008 .rodata tables, 0x0208f044-0x0208f080.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_0208f044: func_ov008_0205bb7c
 *   data_ov008_0208f050: func_ov008_0205bf5c, func_ov008_0205c010, func_ov008_0205c458, func_ov008_0205c4c4
 */

typedef unsigned char u8;
typedef unsigned short u16;

const u8 data_ov008_0208f044[12] = {
    0, 0, 1, 0, 2, 0, 4, 0, 3, 0, 0, 0,
};

const u8 data_ov008_0208f050[48] = {
    62, 0, 0, 0, 63, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0,
    13, 0, 0, 0, 14, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255,
    65, 0, 0, 0, 1, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255,
};
