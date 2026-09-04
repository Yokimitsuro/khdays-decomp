/* ov241 .rodata pointer tables, 0x020d0c84-0x020d0c90.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov241_020d0ca0;
extern int data_ov241_020d0ca8;
extern int data_ov241_020d0cb0;

void *const data_ov241_020d0c84[3] = {

    &data_ov241_020d0cb0,

    &data_ov241_020d0ca8,

    &data_ov241_020d0ca0,

};
