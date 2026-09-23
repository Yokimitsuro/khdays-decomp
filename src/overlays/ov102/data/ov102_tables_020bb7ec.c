/* ov102 .rodata tables, 0x020bb7ec-0x020bb87c.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Spawns the ov102 panel's effect instances around the actor. Builds a rotation matrix (020bb1f4): struct SpawnRing4 data_ov102_020bb7ec; */
const u8 data_ov102_020bb7ec[48] = {
    0, 0, 0, 0, 0, 8, 0, 0, 51, 19, 0, 0, 51, 3, 0, 0,
    205, 12, 0, 0, 205, 20, 0, 0, 205, 252, 255, 255, 51, 19, 0, 0,
    102, 22, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 24, 0, 0,
};

/* read by Spawns the ov102 panel's effect instances around the actor. Builds a rotation matrix (020bb1f4): struct SpawnRing8 data_ov102_020bb81c; */
const u8 data_ov102_020bb81c[96] = {
    0, 32, 0, 0, 205, 12, 0, 0, 0, 0, 0, 0, 0, 224, 255, 255,
    51, 19, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, 205, 12, 0, 0,
    0, 16, 0, 0, 0, 240, 255, 255, 51, 19, 0, 0, 0, 240, 255, 255,
    0, 0, 0, 0, 205, 12, 0, 0, 0, 32, 0, 0, 0, 0, 0, 0,
    51, 19, 0, 0, 0, 224, 255, 255, 0, 240, 255, 255, 205, 12, 0, 0,
    0, 16, 0, 0, 0, 16, 0, 0, 51, 19, 0, 0, 0, 240, 255, 255,
};
