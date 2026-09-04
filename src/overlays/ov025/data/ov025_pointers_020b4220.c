/* ov025 .rodata pointer tables, 0x020b4220-0x020b4228.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov025_020b51dc;
extern int data_ov025_020b51e0;

void *const data_ov025_020b4220[2] = {

    &data_ov025_020b51dc,

    &data_ov025_020b51e0,

};
