/* main .data, 0x02042418-0x02042490: the five party roster entries (0x18 bytes each; 02010e38 points
 * the active-party slots at them, 02010f08 / 020110f4 / 02011134 walk them).
 */
typedef unsigned int u32;

struct PartyRosterEntry {
    u32 field00;
    u32 field04;
    u32 isActive;
    u32 field0c;
    u32 field10;
    u32 field14;
};

struct PartyRosterEntry data_02042418[5] = {
    { 0xffffffff, 0xffffffff, 0, 0, 0xffff0000, 0x00000 },
    { 0xffffffff, 0xffffffff, 0, 1, 0xffff0001, 0x20000 },
    { 0xffffffff, 0xffffffff, 0, 1, 0xffff0002, 0x30000 },
    { 0xffffffff, 0xffffffff, 0, 0, 0xffff0003, 0x40000 },
    { 0xffffffff, 0xffffffff, 0, 0, 0xffff0004, 0x60000 },
};
