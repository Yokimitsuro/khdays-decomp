/* ov298 .rodata tables, 0x020d54f0-0x020d55a4.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Retreat entry of the ov298 enemy: spawns effect 0 and fires reaction 0x177 mode 4 at the + (020d5258): const struct PointTable data_ov298_020d54f0; */
const int data_ov298_020d54f0[45] = {
    68342, 27599, 147456,
    -102400, 14909, -69423,
    135168, 205, -172032,
    114688, 205, 112640,
    113549, -2359, 59298,
    227942, 205, 6640,
    134529, 229, -62730,
    86016, 217, 24658,
    73122, 18014, -184295,
    12636, 27722, -29962,
    -47170, 205, 86209,
    -193044, 205, 182370,
    -81920, 205, 104477,
    38396, 205, 84349,
    49152, 32063, 28672,
};
