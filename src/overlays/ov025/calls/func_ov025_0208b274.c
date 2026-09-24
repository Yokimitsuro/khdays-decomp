/* khdays: shared-bss */
/* Ov025_Hub_SelectMenuGroup -- highlight one of the hub's three menu groups (0: the seven main
 * entries, 1: entries 10/11, 2: entries 12/13), move the selector next to the chosen entry and
 * draw its caption. Twin of ov008 func_ov008_02058df0 (byte-identical code; the ov025 build of
 * the same menu unit). The unused zero-initialised static fixes the order mwcc emits the two
 * local initialiser templates in ([12, 13] before [10, 11]). */
typedef unsigned char u8;

typedef struct {
    int x;
    int y;
} UiLayoutPos;

typedef enum {
    OV008_MENU_ID_NONE = 0
} Ov008MenuId;

typedef struct {
    Ov008MenuId ids[7];
} Ov008MenuIdList7;

typedef struct {
    Ov008MenuId ids[2];
} Ov008MenuIdList2;

typedef struct {
    Ov008MenuIdList2 group2;
    Ov008MenuIdList2 group1;
} Ov008MenuPairGroups;

typedef struct {
    int counts[3];
} Ov008MenuGroupCounts;

typedef struct {
    unsigned int words[4];
} Ov008LayoutTemplate;

typedef struct {
    Ov008MenuId ids[5];
} Ov008MenuIdList5;

typedef struct {
    u8 pad00[0x0c];
    int value0c;
} Ov008MenuEntry;

typedef struct {
    u8 pad00[4];
    u8 variables04[0x48];
    u8 surface4c[0x3c];
    int activeEntryValue88;
    void *entryHandle8c;
    void *entryHandle90;
    int alternateGroupActive94;
} Ov008MenuRenderer;

extern int func_ov025_02084a7c(void);
extern Ov008MenuEntry *func_ov025_0208843c(int context, int id);
extern void func_ov025_020887c0(
    int context, Ov008MenuEntry *entry, int value);
extern void func_ov025_0208884c(
    int context, Ov008MenuEntry *entry, int visible);
extern int func_ov025_0208b0a4(Ov008MenuRenderer *renderer);
extern void func_ov025_0208896c(int context, Ov008MenuEntry *entry);
extern UiLayoutPos *func_ov025_020884c8(int context, Ov008MenuEntry *entry);
extern void func_ov025_02088500(int context, Ov008MenuEntry *entry,
                                UiLayoutPos *position);
extern void *func_ov025_02089894(void *variables, int index);
extern void func_02030158(void *surface);
extern void func_02030278(void *surface, int id, int x, int y,
                          void *buffer, int flags);
extern void func_020300f8(void *surface);


extern const Ov008MenuIdList7 data_ov025_020b38b8;
extern const Ov008MenuGroupCounts data_ov025_020b3888;

void
func_ov025_0208b274(Ov008MenuRenderer *renderer, int selectedGroup)
{
    int itemIndex;
    int groupIndex;
    int context;
    unsigned int notSelected;
    Ov008MenuIdList7 group0 = data_ov025_020b38b8;
    Ov008MenuId group1[2] = {10, 11};
    Ov008MenuId group2[2] = {12, 13};
    /* Original overlay BSS context; shared_bss promotes this symbol at link time. */
    static int data_ov025_020b5744[2] = {0};
    Ov008MenuId *groups[3];
    Ov008MenuGroupCounts counts = data_ov025_020b3888;
    Ov008MenuEntry *entry;
    Ov008MenuEntry *selectorEntry;
    int captionIndex;
    int selectedEntryId;
    UiLayoutPos *selectorPosition;
    UiLayoutPos *selectedPosition;
    UiLayoutPos position;
    void *buffer;
    Ov008MenuId *currentGroup;
    int count;
    unsigned int selected;
    Ov008MenuEntry *loopEntry;


    context = func_ov025_02084a7c();
    groups[0] = group0.ids;
    groups[1] = group1;
    groups[2] = group2;

    for (groupIndex = 0; groupIndex < 3; ++groupIndex) {
        notSelected = selectedGroup != groupIndex;
        itemIndex = 0;
        if ((count = counts.counts[groupIndex]) > 0) {
            selected = notSelected == 0;
            currentGroup = groups[groupIndex];
            do {
                loopEntry = func_ov025_0208843c(
                    context, currentGroup[itemIndex]);
                func_ov025_020887c0(context, loopEntry, notSelected);
                loopEntry = func_ov025_0208843c(
                    context, currentGroup[itemIndex]);
                func_ov025_0208884c(context, loopEntry, selected);
                ++itemIndex;
            } while (itemIndex < count);
        }
    }

    switch (selectedGroup) {
    case 0:
        selectedEntryId = func_ov025_0208b0a4(renderer);
        captionIndex = -1;
        break;
    case 1:
        entry = func_ov025_0208843c(context, 10);
        func_ov025_020887c0(context, entry, renderer->entryHandle8c == 0);
        entry = func_ov025_0208843c(context, 11);
        func_ov025_020887c0(context, entry, renderer->entryHandle90 == 0);
        if (renderer->entryHandle8c != 0) {
            selectedEntryId = 10;
        } else {
            selectedEntryId = 11;
        }
        captionIndex = 0x12;
        break;
    case 2:
        selectedEntryId = 12;
        captionIndex = 13;
        break;
    }

    entry = func_ov025_0208843c(context, selectedEntryId);
    func_ov025_0208896c(context, entry);
    renderer->activeEntryValue88 = entry->value0c;

    selectorEntry = func_ov025_0208843c(context, 0x15);
    selectorPosition = func_ov025_020884c8(context, selectorEntry);
    selectedPosition = func_ov025_020884c8(context, entry);
    position.x = selectorPosition->x;
    position.y = selectedPosition->y;
    func_ov025_02088500(context, selectorEntry, &position);

    renderer->alternateGroupActive94 = selectedGroup != 0;
    if (captionIndex < 0) {
        return;
    }

    buffer = func_ov025_02089894(renderer->variables04, captionIndex);
    func_02030158(renderer->surface4c);
    func_02030278(renderer->surface4c, 0x56, 0, 2, buffer, 1);
    func_020300f8(renderer->surface4c);
}




