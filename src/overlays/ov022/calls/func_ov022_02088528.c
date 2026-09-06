typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Ov002MissionMember {
    char padding000[4];
    u8 nameCode04;
    char padding005[0xff];
} Ov002MissionMember;

typedef struct Ov022EntryRoot {
    u32 flags00;
    char padding004[0x30];
    u8 entryCount34;
    char padding035[7];
    u8 flags3c;
} Ov022EntryRoot;

typedef struct Ov022EntrySystem {
    int field00;
    Ov022EntryRoot *root04;
} Ov022EntrySystem;

typedef struct Ov022ActorEntry {
    u64 flags00;
    u8 field08;
    u8 actorIndex09;
    char padding00a[2];
    int field0c;
    char padding010[0x5c];
    int counter06c;
    char padding070[0x9c];
    int counter10c;
    char padding110[0xac];
    int counter1bc;
    char padding1c0[0x9c];
    int counter25c;
    char padding260[0x45c];
    int resourceIndex6bc;
} Ov022ActorEntry;

extern Ov022EntrySystem data_ov022_020b2e78;
extern u8 data_0204c240;
extern Ov002MissionMember data_0204c678[];

extern Ov022ActorEntry *func_01fffde0(int index);
extern int func_02023588(u32 flagId);
extern void func_020235e8(u32 fieldId, u32 width, u32 value);
extern void func_ov022_0209fb98(Ov022ActorEntry *entry, int enabled, int named);
extern u32 func_ov022_020a0870(u32 *entry, int state);

void func_ov022_02088528(int index)
{
    Ov022ActorEntry *entry;
    Ov022EntryRoot *root;
    Ov002MissionMember *member;

    entry = func_01fffde0(index);
    if (entry == 0) {
        return;
    }

    root = data_ov022_020b2e78.root04;
    entry->counter06c = 0;
    entry->counter10c = 0;
    entry->counter1bc = 0;
    entry->counter25c = 0;

    root->flags3c &= ~1;
    root->flags3c &= ~0x10;
    root->flags3c &= ~2;

    if ((data_0204c240 & 4) == 0 && entry->field0c == 0) {
        member = &data_0204c678[entry->actorIndex09];
        if (func_02023588(0x2089) != 0 || member->nameCode04 == '0') {
            func_020235e8(0x2089, 1, 0);
            func_ov022_0209fb98(entry, 1, 1);
        } else {
            func_ov022_0209fb98(entry, 1, 0);
            entry->resourceIndex6bc = -1;
        }
    }

    if ((entry->flags00 & 0x4000000000000000ULL) != 0) {
        entry->flags00 &= ~0x4000000000000000ULL;
        func_ov022_020a0870((u32 *)entry, 6);
    }
}
