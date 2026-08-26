typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov022DefaultValues {
    u32 values[4];
} Ov022DefaultValues;

typedef struct Ov022UiEntry {
    char pad_0000[4];
    u16 field4;
    char pad_0006[0x1e];
    u8 field24;
    char pad_0025[3];
    u16 field28;
    char pad_002a[6];
} Ov022UiEntry;

typedef struct Ov022UiSubsystem {
    Ov022UiEntry entries[4];
    char pad_00c0[4];
    u16 fieldC4;
    u16 fieldC6;
    u32 flagsC8;
    char pad_00cc[0x18];
    u8 fieldE4;
    char pad_00e5[0x2f];
    u8 field114;
    char pad_0115[0x0f];
    u32 field124;
    u32 field128;
} Ov022UiSubsystem;

extern Ov022DefaultValues data_ov022_020b226c;

extern void *func_020255d4(void *list, int kind, int index);
extern void func_ov002_02050d28(void *destination, void *resource,
                                int enabled);

void func_ov022_02085f9c(Ov022UiSubsystem *subsystem, void *list)
{
    Ov022DefaultValues defaults = data_ov022_020b226c;
    Ov022UiEntry *entry = subsystem->entries;
    u32 *value = defaults.values;
    int i;

    for (i = 0; i < 4; i++) {
        func_ov002_02050d28(entry, func_020255d4(list, 7, 2), 1);
        entry->field4 = 0x10;
        entry->field24 = 0x3e;
        entry->field28 = *value;
        entry++;
        value++;
    }

    func_ov002_02050d28((char *)subsystem + 0xc0,
                         func_020255d4(list, 7, 3), 1);
    subsystem->fieldC4 = 0x10;
    subsystem->fieldC6 = 0x10;
    subsystem->flagsC8 |= 0xf0000;
    subsystem->fieldE4 = 0x3d;

    func_ov002_02050d28((char *)subsystem + 0xf0,
                         func_020255d4(list, 7, 4), 1);
    subsystem->field114 = 0x3d;
    subsystem->field124 = 0;
    subsystem->field128 = 0;
}

