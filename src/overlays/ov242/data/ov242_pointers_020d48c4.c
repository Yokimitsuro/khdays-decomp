/* ov242 .rodata pointer tables, 0x020d48c4-0x020d48d0.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov242_020d48e0;
extern int data_ov242_020d48e8;
extern int data_ov242_020d48f0;

void *const data_ov242_020d48c4[3] = {

    &data_ov242_020d48f0,

    &data_ov242_020d48e8,

    &data_ov242_020d48e0,

};
