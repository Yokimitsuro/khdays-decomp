/* ov002 .data tables, 0x0207f114-0x0207f11c.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Read by Ov002_LoadObjectRecordsAndDrops (0x0207f114, 0x0207f118).
 */

typedef unsigned char u8;
typedef unsigned short u16;

int data_ov002_0207f114[1] = {
    109,
};

int data_ov002_0207f118[1] = {
    0,
};
