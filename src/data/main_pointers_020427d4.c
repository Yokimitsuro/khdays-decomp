/* main .data pointer tables, 0x020427d4-0x020427f0.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_020427b8;
extern int data_020427bc;
extern int data_020427c0;
extern int data_020427c4;
extern int data_020427c8;
extern int data_020427cc;
extern int data_020427d0;

void *data_020427d4[7] = {

    &data_020427d0,

    &data_020427bc,

    &data_020427c8,

    &data_020427c4,

    &data_020427c0,

    &data_020427cc,

    &data_020427b8,

};
