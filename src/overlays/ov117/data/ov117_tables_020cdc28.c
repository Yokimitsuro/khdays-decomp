/* ov117 .rodata tables, 0x020cdc28-0x020cdc44.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov117_020cd2f4 (020cd2f4): Pair data_ov117_020cdc28[];
 *   Publish the landing: copy the pending anchor into the live slot and ask the placement help (020cd494): Pair data_ov117_020cdc28[];
 *   func_ov117_020cd78c (020cd78c): Pair16 data_ov117_020cdc28[]; */
const u8 data_ov117_020cdc28[12] = {
    0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0,
};

/* read by func_ov117_020cbfc4 (020cbfc4): const struct CameraWork data_ov117_020cdc34; */
const int data_ov117_020cdc34[4] = {
    0, 0, 0, 2560,
};
