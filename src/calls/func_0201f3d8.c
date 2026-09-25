/* func_0201f3d8 = ResCache_FindSlot. Looks a resource up in the 128-entry cache table
 * (data_0204bbfc[2], 0x30 bytes each) by `key`: a key with bit 31 set is a numeric id compared with
 * the entries' ids (bit 31 set too), any other key is a name compared (strcmp) with the named
 * entries. Returns the entry, or else the last unused entry seen (0 when the table is full); the
 * caller takes a reference by bumping refCount. */
typedef unsigned short u16;

typedef struct ResCacheEntry {
    u16 refCount;       /* 0x00: 0 = unused */
    char pad02[0xe];
    char name[0x20];    /* 0x10: or an id with bit 31 set */
} ResCacheEntry;

extern ResCacheEntry *data_0204bbfc[];
extern int func_0201fabc(const char *a, const char *b);   /* strcmp */

ResCacheEntry *func_0201f3d8(const char *key)
{
    /* The scan cursor (current entry and its reference count) is a one-element array read through
     * an index that is always 0: its members only become registers once the index is folded,
     * which is the ROM's register assignment (same device as MsgQueue_Init). */
    struct {
        ResCacheEntry *entry;
        u16 refCount;
    } cur[1];
    int n = 0;
    int i;
    ResCacheEntry *unused;
    unsigned int keyIsId = (unsigned int)key & 0x80000000;

    unused = 0;
    cur[n].entry = data_0204bbfc[2];

    for (i = 0; i < 0x80; i++, cur[n].entry++) {
        cur[n].refCount = cur[n].entry->refCount;

        if (cur[n].refCount != 0) {
            unsigned int id = *(unsigned int *)cur[n].entry->name;
            unsigned int entryIsId = id & 0x80000000;

            if (keyIsId != 0 && entryIsId != 0) {
                if ((unsigned int)key == id) {
                    return cur[n].entry;
                }
            }
            if (keyIsId == 0 && entryIsId == 0) {
                if (func_0201fabc(cur[n].entry->name, key) == 0) {
                    return cur[n].entry;
                }
            }
        }
        if (cur[n].refCount == 0) {
            unused = cur[n].entry;
        }
    }
    return unused;
}
