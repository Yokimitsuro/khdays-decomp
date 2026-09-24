/* Adds (`add` set) or sets an item stack in save record `slot`: an existing entry
 * (func_0203583c) takes the new count (added to its own when adding), clamped to 0..0xffff, and is
 * freed when it drops to 0; otherwise a non-empty stack goes to the first free of the 24 entries
 * (+0x3c). Adding an empty stack does nothing. */
#pragma thumb on
typedef unsigned short u16;
typedef short s16;

typedef struct {
    u16 id;
    s16 count;
} ItemEntry;

typedef struct {
    char pad[0x3c];
    ItemEntry items[24];    /* 0x3c */
    char pad9c[0x104 - 0x9c];
} SlotRecord;

extern ItemEntry *func_0203583c(int slot, u16 id);
extern SlotRecord data_0204c678[];

void func_0203514c(int slot, ItemEntry *item, int add)
{
    int off = slot * 0x104;
    ItemEntry *e;
    int i;

    if (add) {
        if (item->id == 0 || item->count == 0) {
            return;
        }
    }
    e = func_0203583c(slot, item->id);
    if (e != 0) {
        int v;

        if (add) {
            v = e->count + item->count;
        } else {
            v = item->count;
        }
        if (v > 0xffff) {
            v = 0xffff;
        } else if (v < 0) {
            v = 0;
        }
        e->count = v;
        if (e->count == 0) {
            e->id = 0;
        }
        return;
    }
    if (item->count == 0) {
        return;
    }
    e = ((SlotRecord *)((char *)data_0204c678 + off))->items;
    for (i = 0; i < 24; i++, e++) {
        if (e->id == 0) {
            e->id = item->id;
            e->count = item->count;
            return;
        }
    }
}
