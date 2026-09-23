/* ov253 .rodata pointer tables, 0x020d4940-0x020d4950.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov253_020d4ba0;
extern int data_ov253_020d4ba8;
extern int data_ov253_020d4bb0;
extern int data_ov253_020d4bb8;

void *const data_ov253_020d4940[4] = {

    &data_ov253_020d4bb8,

    &data_ov253_020d4bb0,

    &data_ov253_020d4ba8,

    &data_ov253_020d4ba0,

};
