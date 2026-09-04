/* ov237 .rodata pointer tables, 0x020d19f8-0x020d1a20.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov237_020d1c20;
extern int data_ov237_020d1c28;
extern int data_ov237_020d1c30;
extern int data_ov237_020d1c38;
extern int data_ov237_020d1c40;
extern int data_ov237_020d1c4c;
extern int data_ov237_020d1c58;
extern int data_ov237_020d1c64;
extern int data_ov237_020d1c70;
extern int data_ov237_020d1c7c;

void *const data_ov237_020d19f8[10] = {

    &data_ov237_020d1c64,

    &data_ov237_020d1c40,

    &data_ov237_020d1c4c,

    &data_ov237_020d1c28,

    &data_ov237_020d1c30,

    &data_ov237_020d1c58,

    &data_ov237_020d1c70,

    &data_ov237_020d1c7c,

    &data_ov237_020d1c38,

    &data_ov237_020d1c20,

};
