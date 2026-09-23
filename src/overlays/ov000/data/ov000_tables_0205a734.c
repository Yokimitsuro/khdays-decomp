/* ov000 .rodata tables, 0x0205a734-0x0205a858.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Scene 1: build the three text surfaces of the page. (020500d0): const TileSurfaceCfg data_ov000_0205a734; */
const int data_ov000_0205a734[10] = {
    0, 14, 18, 2, 97, 15, 0, 23,
    0, 32,
};

/* read by Scene 1: build the three text surfaces of the page. (020500d0): const TileSurfaceCfg data_ov000_0205a75c; */
const int data_ov000_0205a75c[10] = {
    4, 0, 32, 13, 133, 15, 0, 23,
    0, 32,
};

/* read by Scene 1: build the three text surfaces of the page. (020500d0): const TileSurfaceCfg data_ov000_0205a784; */
const int data_ov000_0205a784[10] = {
    17, 0, 32, 6, 549, 15, 0, 23,
    0, 32,
};

/* read by func_ov000_0204fdac (0204fdac): const int data_ov000_0205a7ac[4][8];
 *   func_ov000_020506d0 (020506d0): Ov000EntryIdGrid data_ov000_0205a7ac;
 *   Page-scroll tick for the ov000 title/menu stack: eases each of the four selection (02050ec4): const int data_ov000_0205a7ac[4][8];
 *   func_ov000_02051470 (02051470): const NumberDisplayConfig data_ov000_0205a7ac[3]; */
const int data_ov000_0205a7ac[32] = {
    1, 31, 34, 37, 40, 50, 51, 52,
    2, 32, 35, 38, 41, 53, 54, 55,
    3, 33, 36, 39, 42, 56, 57, 58,
    4, 0, 0, 0, 0, 0, 0, 0,
};

/* read by func_ov000_02053b0c (02053b0c): EntryIdGroup3 data_ov000_0205a82c; */
const int data_ov000_0205a82c[3] = {
    2, 3, 4,
};

/* read by flush dirty logo BG layers to VRAM, ov000. For each of the 4 (02054668): int  data_ov000_0205a838[]; */
const int data_ov000_0205a838[4] = {
    24, 25, 26, 27,
};

/* read by func_ov000_02053b0c (02053b0c): EntryIdGroup4 data_ov000_0205a848; */
const int data_ov000_0205a848[4] = {
    5, 6, 7, 8,
};
