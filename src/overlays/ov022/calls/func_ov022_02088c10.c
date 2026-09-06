typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;

typedef struct Ov022RosterRow {
    void *owner00;
    char padding004[0x06];
    u8 playerIndex0a;
    char padding00b;
} Ov022RosterRow;

typedef struct Ov022EntryRoot {
    int flags00;
    Ov022RosterRow rows04[4];
    char padding034[0x09];
    s8 activeSpot3d;
    char padding03e[0x02];
    int spotTimer40;
} Ov022EntryRoot;

typedef struct Ov022EntrySystem {
    int callback00;
    Ov022EntryRoot *root04;
} Ov022EntrySystem;

extern Ov022EntrySystem data_ov022_020b2e78;

extern unsigned int func_02030788(void);
extern void func_02033b24(int bank, int sound);
extern void func_ov002_02056de0(int resourceId, int enabled);

void func_ov022_02088c10(int index, unsigned int resourceId, int spot)
{
    Ov022EntryRoot *root;

    root = data_ov022_020b2e78.root04;
    if (root == 0) {
        return;
    }

    if (data_ov022_020b2e78.root04->rows04[index].playerIndex0a !=
        func_02030788()) {
        return;
    }

    if (spot != root->activeSpot3d) {
        func_02033b24(0, 4);
        func_ov002_02056de0((u16)resourceId, 0);
        root->activeSpot3d = (s8)spot;
    } else if (resourceId == 0xffff) {
        func_02033b24(0, 4);
    }

    root->spotTimer40 = 0x1e000;
}
