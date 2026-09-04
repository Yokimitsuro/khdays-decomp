/* ov023 .rodata pointer tables, 0x02089d14-0x02089d74.
 *
 * 2 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_ov023_0208a018;
extern int data_ov023_0208a01c;
extern int data_ov023_0208a020;
extern int data_ov023_0208a024;
extern int data_ov023_0208a028;
extern int data_ov023_0208a02c;
extern int data_ov023_0208a030;
extern int data_ov023_0208a034;

void *const data_ov023_02089d14[12] = {

    &data_ov023_0208a024,

    &data_ov023_0208a018,

    &data_ov023_0208a034,

    &data_ov023_0208a030,

    0,

    &data_ov023_0208a01c,

    0,

    0,

    &data_ov023_0208a02c,

    &data_ov023_0208a028,

    0,

    &data_ov023_0208a020,

};

void *const data_ov023_02089d44[12] = {

    &data_ov023_0208a024,

    &data_ov023_0208a018,

    &data_ov023_0208a034,

    &data_ov023_0208a030,

    0,

    &data_ov023_0208a01c,

    0,

    0,

    &data_ov023_0208a02c,

    &data_ov023_0208a028,

    0,

    &data_ov023_0208a020,

};
