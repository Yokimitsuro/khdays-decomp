typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Ov022SeatEntry {
    char padding000[0x09];
    u8 nActorIndex09;
    char padding00a[0x5c];
    s16 nSlotId66;
} Ov022SeatEntry;

typedef struct Ov022EntryOwner {
    char padding000[0x20];
    Ov022SeatEntry *actor20;
} Ov022EntryOwner;

typedef struct Ov022RosterRow {
    Ov022EntryOwner *owner00;
    char padding004[0x06];
    u8 playerIndex0a;
    char padding00b;
} Ov022RosterRow;

typedef struct Ov022EntryRoot {
    char padding000[0x04];
    Ov022RosterRow rows04[1];
} Ov022EntryRoot;

typedef struct Ov022EntrySystem {
    int callback00;
    Ov022EntryRoot *root04;
} Ov022EntrySystem;

extern Ov022EntrySystem data_ov022_020b2e78;

extern Ov022SeatEntry *func_01fffde0(int index);
extern unsigned int func_02030788(void);
extern void func_ov022_020aa824(Ov022SeatEntry *entry, int value, int id, int delta);
extern int func_ov002_0206d0e0(int id);
extern VecFx32 *func_ov022_020881f8(int index);
extern void func_ov002_0206dd1c(int context, int key, int value, u16 id);
extern int func_ov002_02072754(int group);
extern void *func_ov002_02077b64(int index, int value, u16 id, int group,
                                 const VecFx32 *position, int unused, int level);

void func_ov022_02088a5c(int index, int id, unsigned int value, unsigned int level)
{
    Ov022SeatEntry *entry;
    int mappedValue;
    VecFx32 position;

    entry = func_01fffde0(index);
    if (entry == 0) {
        return;
    }

    if (func_02030788() == 0 ||
        data_ov022_020b2e78.root04->rows04[index].playerIndex0a == func_02030788()) {
        func_ov022_020aa824(entry, value, id, -1);
    }

    mappedValue = func_ov002_0206d0e0((s16)id);
    position = *func_ov022_020881f8(index);
    position.y += 0x800;

    func_ov002_0206dd1c(entry->nActorIndex09, value & 0xff, mappedValue & 0xff, id);
    func_ov002_02077b64(value, mappedValue, id,
                        (u16)func_ov002_02072754(entry->nSlotId66),
                        &position, 0, level);
}
