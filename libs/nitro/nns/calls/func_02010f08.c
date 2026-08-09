typedef unsigned int u32;
typedef unsigned short u16;

struct PartyRosterEntry {
    u32 field00;
    u32 field04;
    u32 isActive;
    u32 field0c;
    u32 field10;
    u32 field14;
};

extern u16 data_02047360;
extern struct PartyRosterEntry data_02042418[];

void func_02010f08(void)
{
    int i;
    struct PartyRosterEntry *entry;
    u32 activeCount;

    activeCount = data_02047360;
    entry = data_02042418;

    if (activeCount > 1) {
        activeCount++;
    }

    for (i = 0; i < 5; i++) {
        if (i < (int)activeCount) {
            entry->isActive = 1;
        } else {
            entry->isActive = 0;
        }
        if (entry->field0c != 0) {
            entry->field00 = 0;
            entry->field04 = 0x10000;
        } else {
            entry->field00 = 0;
            entry->field04 = 0x20000;
        }
        entry++;
    }
}
