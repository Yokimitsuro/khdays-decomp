/* ov187 .rodata tables, 0x020d70f0-0x020d711c.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov187_020d3848 (020d3848): const struct CameraWork data_ov187_020d70f0; */
const int data_ov187_020d70f0[4] = {
    0, 0, 0, 3072,
};

/* read by func_ov187_020d67bc (020d67bc): Pair data_ov187_020d7100[];
 *   Publish the landing: copy the pending anchor into the live slot and ask the placement help (020d695c): Ev data_ov187_020d7100[];
 *   func_ov187_020d6c54 (020d6c54): Pair16 data_ov187_020d7100[]; */
const u8 data_ov187_020d7100[12] = {
    0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0,
};

/* read by func_ov187_020d548c (020d548c): const struct CameraWork data_ov187_020d710c; */
const int data_ov187_020d710c[4] = {
    0, 0, 0, 2560,
};
