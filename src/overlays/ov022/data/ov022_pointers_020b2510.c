/* ov022 .rodata pointer tables, 0x020b2510-0x020b2520.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov022_020b2be8;
extern int data_ov022_020b2bf8;
extern int data_ov022_020b2c08;
extern int data_ov022_020b2c18;

void *const data_ov022_020b2510[4] = {

    &data_ov022_020b2c18,

    &data_ov022_020b2c08,

    &data_ov022_020b2bf8,

    &data_ov022_020b2be8,

};
