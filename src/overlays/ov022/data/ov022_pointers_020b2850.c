/* ov022 .rodata pointer tables, 0x020b2850-0x020b2874.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov022_020b2dc4;
extern int data_ov022_020b2dcc;
extern int data_ov022_020b2dd4;
extern int data_ov022_020b2ddc;
extern int data_ov022_020b2de4;
extern int data_ov022_020b2dec;
extern int data_ov022_020b2df4;
extern int data_ov022_020b2dfc;

void *const data_ov022_020b2850[9] = {

    &data_ov022_020b2dc4,

    &data_ov022_020b2ddc,

    &data_ov022_020b2dcc,

    &data_ov022_020b2de4,

    &data_ov022_020b2df4,

    &data_ov022_020b2dd4,

    &data_ov022_020b2dec,

    &data_ov022_020b2dfc,

    &data_ov022_020b2df4,

};
