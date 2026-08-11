typedef unsigned int u32;

typedef struct VBlankCallbackEntry VBlankCallbackEntry;

struct VBlankCallbackEntry {
    int active;
    char name[16];
    void (*callback)(void);
    VBlankCallbackEntry *next;
    VBlankCallbackEntry *previous;
};

extern VBlankCallbackEntry data_027e0090[4];
extern VBlankCallbackEntry *data_027e008c;

extern u32 strlen(const char *string);
extern int strncmp(const char *left, const char *right, u32 length);
extern int OS_DisableIrqMask(u32 mask);
extern int OS_EnableIrqMask(u32 mask);

void func_02000fb4(int unused, const char *name)
{
    VBlankCallbackEntry **storeAddress;
    int found = 0;
    VBlankCallbackEntry *entry = data_027e0090;
    const char *searchName = name;
    int index = found;

    storeAddress = &data_027e008c;
    do {
        if (strncmp(entry->name, searchName, strlen(entry->name)) == 0 &&
            entry->active != 0) {
            found = 1;
            break;
        }
        index++;
        entry++;
    } while (index < 4);

    if (found != 0) {
        VBlankCallbackEntry *next;
        VBlankCallbackEntry *previous;
        VBlankCallbackEntry *head;

        OS_DisableIrqMask(1);
        next = entry->next;
        previous = entry->previous;
        if (previous != 0) {
            previous->next = next;
        }
        if (next != 0) {
            next->previous = previous;
        }
        entry->active = 0;
        head = data_027e008c;
        if (head == entry) {
            previous = entry->next;
            *storeAddress = previous;
        }
        OS_EnableIrqMask(1);
    }
}
