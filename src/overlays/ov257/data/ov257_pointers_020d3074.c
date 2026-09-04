/* ov257 .rodata pointer tables, 0x020d3074-0x020d3094.
 *
 * 2 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov257_020d3360;
extern int data_ov257_020d336c;
extern int data_ov257_020d3378;
extern int data_ov257_020d3384;
extern int data_ov257_020d3390;
extern int data_ov257_020d339c;
extern int data_ov257_020d33a8;
extern int data_ov257_020d33b4;

void *const data_ov257_020d3074[4] = {

    &data_ov257_020d339c,

    &data_ov257_020d3390,

    &data_ov257_020d33b4,

    &data_ov257_020d33a8,

};

void *const data_ov257_020d3084[4] = {

    &data_ov257_020d3360,

    &data_ov257_020d3384,

    &data_ov257_020d3378,

    &data_ov257_020d336c,

};
