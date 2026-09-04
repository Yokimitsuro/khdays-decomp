/* ov025 .rodata pointer tables, 0x020b3934-0x020b3940.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov025_020b4ca0;

void *const data_ov025_020b3934[3] = {

    &data_ov025_020b4ca0,

    0,

    0,

};
