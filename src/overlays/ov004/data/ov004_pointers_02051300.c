/* ov004 .data pointer tables, 0x02051300-0x02051328.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov004_02051224;
extern int data_ov004_02051238;
extern int data_ov004_0205124c;
extern int data_ov004_02051260;
extern int data_ov004_02051274;
extern int data_ov004_02051288;
extern int data_ov004_0205129c;
extern int data_ov004_020512b0;
extern int data_ov004_020512c4;
extern int data_ov004_020512d8;

void *data_ov004_02051300[10] = {

    &data_ov004_020512d8,

    &data_ov004_0205124c,

    &data_ov004_020512b0,

    &data_ov004_0205129c,

    &data_ov004_02051274,

    &data_ov004_02051288,

    &data_ov004_02051260,

    &data_ov004_02051224,

    &data_ov004_02051238,

    &data_ov004_020512c4,

};
