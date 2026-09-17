/* main .data pointer tables, 0x020423ec-0x02042418.
 *
 * 6 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern void func_02010e18(void);
extern void func_02010e20(void);
extern void func_02010e28(void);
extern void func_02010e30(void);

/* The five party roster entries (src/data/main_party_roster_02042418.c). */
typedef struct PartyRosterEntry { unsigned int w[6]; } PartyRosterEntry;
extern PartyRosterEntry data_02042418[5];

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

    &data_02042418[0],

    &data_02042418[3],

};

void *data_02042404[5] = {

    &data_02042418[4],

    &data_02042418[3],

    &data_02042418[0],

    &data_02042418[2],

    &data_02042418[1],

};
