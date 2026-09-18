/* ov243 .rodata pointer tables, 0x020d4748-0x020d4754.
 *
 * 1 table: the joint names the constructor (020d393c) resolves on the +0x384 item; only the
 * first entry is set. All zero in the ROM image because the entry is a relocation.
 */

extern char data_ov243_020d4760[];

void *const data_ov243_020d4748[3] = {

    data_ov243_020d4760,

    0,

    0,

};
