typedef signed char s8;
typedef unsigned char u8;

typedef struct Item Item;
typedef void (*ItemCallback)(Item *item);

/*
 * An entry on the object's node list. The list itself is walked by
 * func_01fffd70 / func_01fffd8c, which return the item pointer stored at
 * offset 0xc of each node.
 */
struct Item {
    int field_00;
    int field_04;
    ItemCallback updateCallbacks[3]; /* 0x08, 0x0c, 0x10 */
    ItemCallback pendingCallback;    /* 0x14 */
    ItemCallback field_18;
    int field_1c;
    s8 field_20;                     /* which callback slot is running */
    u8 pad_21[3];
    int field_24;                    /* non-zero: item wants to be torn down */
};

typedef struct Owner {
    u8 pad_00[0x28];
    int updateCount; /* 0x28 */
    int scaledTime;  /* 0x2c */
} Owner;

extern Item *func_01fffd70(Owner *owner);
extern Item *func_01fffd8c(Owner *owner);
extern void func_0203c424(Owner *owner, Item *item);

void func_0203c4a8(Owner *owner, int tick)
{
    Item *item;
    s8 pendingSlot;
    int slot;

    owner->scaledTime = (int)(((long long)tick * 0x88 + 0x800) >> 12);

    pendingSlot = 1;
    item = func_01fffd70(owner);
    while (item != 0) {
        if (item->pendingCallback != 0) {
            item->field_20 = pendingSlot;
            item->pendingCallback(item);
            item->pendingCallback = 0;
        }
        item = func_01fffd8c(owner);
    }

    for (slot = 0; slot < 3; slot++) {
        item = func_01fffd70(owner);
        while (item != 0) {
            if (item->field_24 == 0 && item->updateCallbacks[slot] != 0) {
                item->field_20 = (s8)slot;
                item->updateCallbacks[slot](item);
            }
            item = func_01fffd8c(owner);
        }
    }

    /*
     * Tearing an item down re-links the list, so the walk restarts from the
     * head after every removal and only advances when nothing was removed.
     * The shared re-check block is what the original emits; an if/else loop
     * duplicates the "next" call and compiles 8 bytes long.
     */
restart:
    item = func_01fffd70(owner);
    if (item == 0) {
        goto done;
    }
check:
    if (item->field_24 != 0) {
        func_0203c424(owner, item);
        goto restart;
    }
    item = func_01fffd8c(owner);
    if (item != 0) {
        goto check;
    }
done:
    owner->updateCount++;
}
