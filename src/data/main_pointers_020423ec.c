/* main .data pointer tables, 0x020423ec-0x02042418.
 *
 * 6 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern void func_02010e18(void);
extern void func_02010e20(void);
extern void func_02010e28(void);
extern void func_02010e30(void);
extern int data_02042418;
extern int data_02042430;
extern int data_02042448;
extern int data_02042460;
extern int data_02042478;

void *data_020423ec[1] = {

    (void *)func_02010e18,

};

void *data_020423f0[1] = {

    (void *)func_02010e20,

};

void *data_020423f4[1] = {

    (void *)func_02010e28,

};

void *data_020423f8[1] = {

    (void *)func_02010e30,

};

void *data_020423fc[2] = {

    &data_02042418,

    &data_02042460,

};

void *data_02042404[5] = {

    &data_02042478,

    &data_02042460,

    &data_02042418,

    &data_02042448,

    &data_02042430,

};
