/* ov022 .rodata pointer tables, 0x020b25a8-0x020b25b4.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov022_020b2c9c;
extern int data_ov022_020b2cb0;
extern int data_ov022_020b2cc4;

void *const data_ov022_020b25a8[3] = {

    &data_ov022_020b2c9c,

    &data_ov022_020b2cb0,

    &data_ov022_020b2cc4,

};
