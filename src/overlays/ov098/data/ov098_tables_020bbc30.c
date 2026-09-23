/* ov098 .rodata tables, 0x020bbc30-0x020bbc54.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by * Attack step: the per-frame body of the ov042 enemy's attack state. (020bae74): Angles data_ov098_020bbc30; */
const u8 data_ov098_020bbc30[12] = {
    0, 0, 0, 0, 85, 21, 0, 0, 171, 234, 255, 255,
};

/* read by * Attack step: the per-frame body of the ov042 enemy's attack state. (020bae74): const Vec3 data_ov098_020bbc3c; */
const u8 data_ov098_020bbc3c[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
};

/* read by * Attack step: the per-frame body of the ov042 enemy's attack state. (020bae74): Vec3 data_ov098_020bbc48; */
const u8 data_ov098_020bbc48[12] = {
    31, 1, 0, 0, 20, 22, 0, 0, 246, 16, 0, 0,
};
