/* ov284 .rodata pointer tables, 0x020cd5a4-0x020cd5b4.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov284_020cd5e0;
extern int data_ov284_020cd5e8;
extern int data_ov284_020cd5f0;
extern int data_ov284_020cd5f8;

void *const data_ov284_020cd5a4[4] = {

    &data_ov284_020cd5f8,

    &data_ov284_020cd5f0,

    &data_ov284_020cd5e8,

    &data_ov284_020cd5e0,

};
