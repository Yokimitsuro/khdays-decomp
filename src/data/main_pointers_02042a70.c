/* main .data pointer tables, 0x02042a70-0x02042ac0.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern int data_02042a20;
extern int data_02042a24;
extern int data_02042a28;
extern int data_02042a2c;
extern int data_02042a30;
extern int data_02042a34;
extern int data_02042a38;
extern int data_02042a3c;
extern int data_02042a40;
extern int data_02042a44;
extern int data_02042a48;
extern int data_02042a4c;
extern int data_02042a50;
extern int data_02042a54;
extern int data_02042a58;
extern int data_02042a5c;
extern int data_02042a60;
extern int data_02042a64;
extern int data_02042a68;
extern int data_02042a6c;

void *data_02042a70[20] = {

    &data_02042a50,

    &data_02042a5c,

    &data_02042a60,

    &data_02042a68,

    &data_02042a38,

    &data_02042a6c,

    &data_02042a30,

    &data_02042a64,

    &data_02042a2c,

    &data_02042a24,

    &data_02042a28,

    &data_02042a54,

    &data_02042a3c,

    &data_02042a40,

    &data_02042a44,

    &data_02042a48,

    &data_02042a4c,

    &data_02042a20,

    &data_02042a58,

    &data_02042a34,

};
