/* ov002 .data tables, 0x0207e734-0x0207e764.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Read by Ov002_TickCameraTransition (0x0207e734, 0x0207e73c).
 */

typedef unsigned char u8;
typedef unsigned short u16;

int data_ov002_0207e734[1] = {
    96,
};

int data_ov002_0207e738[1] = {
    1024,
};

int data_ov002_0207e73c[10] = {
    4, 128, 2048, 4, 0, 1024, 4, 0,
    2048, 4,
};
