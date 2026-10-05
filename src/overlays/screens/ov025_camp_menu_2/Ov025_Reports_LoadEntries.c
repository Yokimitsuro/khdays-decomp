/* Ov025_Reports_LoadEntries -- load the report/enemy entry table (mi/mi/eid.z) and the mode sprite
 * file, build the 0x40-byte runtime entries (lengths, texts, sprite cells, name pointers) and, in
 * enemy mode, copy them into the second half of the allocation. */

#include "nitro/types.h"
#include "game/engine.h"

struct DbName { short id; short pad; };

typedef struct SpriteResSet {
    void *screen;
    void *character;
    void *palette;
} SpriteResSet;

typedef struct Ov025RawEntry {
    u16 id : 9;
    u16 flag9 : 1;
    u16 flag10 : 1;
    u16 padFlags : 5;
    u16 len0;
    u16 len1;
    u16 len2;
    u8 pad08[0xc];
} Ov025RawEntry;

typedef struct Ov025Entry {
    u16 id : 9;
    u16 flag9 : 1;
    u16 pending : 6;
    u16 len0;
    u16 len1;
    u16 len2;
    s16 spriteIndex;
    u8 valid;
    u8 wrapped;
    struct Ov025Entry *duplicate;
    void *text0;
    void *text1;
    void *text2;
    SpriteResSet sprite;
    void *names[6];
} Ov025Entry;

typedef struct Ov025Page {
    u8 pad000[0x1e8];
    Ov025Entry *entries;
    u8 pad1ec[0x230 - 0x1ec];
    void *table;
    void *spriteFile;
    u8 pad238[0x258 - 0x238];
    int mode;
} Ov025Page;

extern Ov025Page *Ov025_GetPageA(void);
extern void *Archive_LoadFile(u32 path, int heap);
extern int OS_SNPrintf(char *dst, unsigned int len, const char *fmt, ...);
extern u32 Ov025_PackSlotTag(int member);
extern void *NNSi_FndAllocFromDefaultExpHeap(u32 size);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern int Ov025_IsFlagRowFree(int index);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

extern char gOv025MiMiEidPath[];
extern const char *data_ov025_020b4220[];
extern char gOv025UiCmStrPathFmt[];
extern const u8 data_ov025_020b4228[]; /* Ov025ReportsSet[2]; +4 = the entries' sprite member tag */

void Ov025_Reports_LoadEntries(void)
{
    int maxNames;
    int i;
    Ov025Entry *entry;
    Ov025RawEntry *raw;
    void *itemFile;
    Ov025Page *page;
    u32 modeZero;
    u32 n;
    u32 usedSprite;
    u8 *text;
    u32 *table;
    char path[0x20];
    SpriteResSet sprite;
    int wrapped;
    int prevId;
    u32 offset;
    int freeRow;
    int spriteIndex;
    void *msg;
    void *name;

    page = Ov025_GetPageA();
    usedSprite = 0;
    wrapped = 0;
    modeZero = page->mode == 0;
    prevId = 0;
    /* Reuse this local for the query result to preserve MWCC register allocation. */
    itemFile = (void *)GameState_GetField(0x44e, 3);
    maxNames = (int)itemFile;
    itemFile = 0;
    if (maxNames < 6) {
        maxNames++;
    }
    raw = (Ov025RawEntry *)page;
    if (!modeZero) {
        itemFile = Archive_LoadFile((u32)gOv025MiMiEidPath, 0xe);
        MsgDb_LoadDb(0x15, 0xe);
    }
    OS_SNPrintf(path, 0x20, gOv025UiCmStrPathFmt, data_ov025_020b4220[page->mode]);
    table = Archive_LoadFile((u32)path, 0xe);
    page->spriteFile = Archive_LoadFile(Ov025_PackSlotTag((data_ov025_020b4228 + 4)[((Ov025Page *)raw)->mode * 5]), 0xe);
    if (modeZero) {
        page->entries = NNSi_FndAllocFromDefaultExpHeap(*table << 6);
        MI_CpuFill8(page->entries, 0, *table << 6);
    } else {
        page->entries = NNSi_FndAllocFromDefaultExpHeap(*table << 7);
        MI_CpuFill8(page->entries, 0, *table << 7);
    }
    text = (u8 *)(table + 1) + *table * 0x14;
    if (!modeZero) {
        Res_LoadSpriteSet(&sprite, page->spriteFile, 0, 0, 0);
    }
    n = 0;
    if (n < *table) {
        offset = 0;
        raw = (Ov025RawEntry *)(table + 1);
        int checkFree = !modeZero;
        do {
            entry = (Ov025Entry *)((u8 *)page->entries + offset);
            if (checkFree) {
                freeRow = Ov025_IsFlagRowFree(*(u8 *)raw);
            } else {
                freeRow = 0;
            }
            if (!wrapped && modeZero) {
                if (raw->id < prevId) {
                    wrapped = 1;
                } else {
                    prevId = raw->id;
                }
            }
            if (modeZero) {
                entry->id = raw->id;
                entry->flag9 = raw->flag9;
            } else {
                entry->id = *(u8 *)raw;
                entry->flag9 = 0;
            }
            if (!wrapped && (!modeZero || raw->flag10)) {
                if (modeZero) {
                    spriteIndex = usedSprite;
                } else if (!freeRow) {
                    spriteIndex = ((u8 *)raw)[1];
                } else {
                        spriteIndex = (s16)-1;
                        entry->sprite = sprite;
                        entry->spriteIndex = 0;
                }
                if (spriteIndex >= 0) {
                    Res_LoadSpriteSet(&entry->sprite, page->spriteFile, spriteIndex, spriteIndex, spriteIndex);
                    entry->spriteIndex = spriteIndex;
                }
                usedSprite++;
            } else {
                entry->spriteIndex = -1;
            }
            entry->pending = freeRow;
            entry->len0 = raw->len0;
            entry->len1 = raw->len1;
            entry->len2 = raw->len2;
            entry->text0 = text;
            entry->text1 = text + raw->len0 * 2;
            entry->text2 = (u8 *)entry->text1 + raw->len1 * 2;
            text = (u8 *)entry->text2 + raw->len2 * 2;
            entry->valid = 1;
            entry->wrapped = wrapped;
            if (!modeZero) {
                for (i = 0; i < (int)maxNames; i++) {
                    int msgId = ((struct DbName *)((u8 *)itemFile + entry->id * 0x18 + 4))[i].id;
                    if (msgId > 0) {
                        msg = 0;
                        MsgDb_FetchRecord(&msg, 0x15, msgId, 0xe);
                        name = NNSi_FndAllocFromDefaultExpHeap(*(u32 *)((u8 *)msg + 0x94) << 1);
                        MI_CpuCopy8(*(void **)((u8 *)msg + 0xc), name, *(u32 *)((u8 *)msg + 0x94) << 1);
                        entry->names[i] = name;
                        DispatchByNodeKind(&msg);
                    }
                }
                MI_CpuCopy8(entry, (u8 *)entry + *table * 0x40, 0x40);
                entry->duplicate = (Ov025Entry *)((u8 *)entry + *table * 0x40);
                entry->duplicate->wrapped = 1;
                entry->duplicate->spriteIndex = -1;
            } else {
                entry->duplicate = 0;
            }
            raw++;
            offset += 0x40;
            n++;
        } while (n < *table);
    }
    page->table = table;
    if (itemFile != 0) {
        ResSlot_Release_2(0x15);
        NNSi_FndFreeFromDefaultHeap(itemFile);
    }
}

