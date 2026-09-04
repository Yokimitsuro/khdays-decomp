/* ov005 .data pointer tables, 0x0205b79c-0x0205b7a8.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov005_0205b7a8;
extern int data_ov005_0205b7b8;
extern int data_ov005_0205b7e0;

void *data_ov005_0205b79c[3] = {

    &data_ov005_0205b7b8,

    &data_ov005_0205b7a8,

    &data_ov005_0205b7e0,

};
