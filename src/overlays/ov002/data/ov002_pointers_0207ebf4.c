/* ov002 .data pointer tables, 0x0207ebf4-0x0207ec00.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov002_0207ed74;
extern int data_ov002_0207ee84;
extern int data_ov002_0207eee8;

void *data_ov002_0207ebf4[3] = {

    &data_ov002_0207ed74,

    &data_ov002_0207ee84,

    &data_ov002_0207eee8,

};
