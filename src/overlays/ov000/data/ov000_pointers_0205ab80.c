/* ov000 .data pointer tables, 0x0205ab80-0x0205ab88.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov000_0205ab88;

void *data_ov000_0205ab80[2] = {

    &data_ov000_0205ab88,

    &data_ov000_0205ab88,

};
