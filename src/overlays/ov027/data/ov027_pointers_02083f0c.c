/* ov027 .data pointer tables, 0x02083f0c-0x02083f24.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov027_02083f54;
extern int data_ov027_02084104;
extern int data_ov027_02084148;
extern int data_ov027_020841e0;
extern int data_ov027_02084238;
extern int data_ov027_02084294;

void *data_ov027_02083f0c[6] = {

    &data_ov027_02083f54,

    &data_ov027_02084148,

    &data_ov027_02084238,

    &data_ov027_02084104,

    &data_ov027_020841e0,

    &data_ov027_02084294,

};
