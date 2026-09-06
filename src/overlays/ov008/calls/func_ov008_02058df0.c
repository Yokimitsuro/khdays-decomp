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

extern int func_ov008_02050c54(void);
extern Ov008MenuEntry *func_ov008_02054788(int context, int id);
extern void func_ov008_02054b18(
    int context, Ov008MenuEntry *entry, int value);
extern void func_ov008_02054ba4(
    int context, Ov008MenuEntry *entry, int visible);
extern int func_ov008_02058c20(Ov008MenuRenderer *renderer);
extern void func_ov008_02054cc4(int context, Ov008MenuEntry *entry);
extern UiLayoutPos *func_ov008_02054820(int context, Ov008MenuEntry *entry);
extern void func_ov008_02054858(int context, Ov008MenuEntry *entry,
                                UiLayoutPos *position);
extern void *func_ov008_02055c84(void *variables, int index);
extern void func_02030158(void *surface);
extern void func_02030278(void *surface, int id, int x, int y,
                          void *buffer, int flags);
extern void func_020300f8(void *surface);

const Ov008LayoutTemplate data_ov008_0208e918 = {{0, 1, 0, 0}};
static const Ov008MenuIdList5 sInitialMenuEntries = {{1, 2, 3, 4, 5}};

void
func_ov008_02058df0(Ov008MenuRenderer *renderer, int selectedGroup)
{
    int itemIndex;
    int groupIndex;
    int context;
    unsigned int notSelected;
    Ov008MenuIdList7 group0 = {{1, 2, 5, 3, 4, 6, 9}};
    Ov008MenuId group1[2] = {10, 11};
    Ov008MenuId group2[2] = {12, 13};
    Ov008MenuId *groups[3];
    Ov008MenuGroupCounts counts = {{7, 2, 2}};
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


    context = func_ov008_02050c54();
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
                loopEntry = func_ov008_02054788(
                    context, currentGroup[itemIndex]);
                func_ov008_02054b18(context, loopEntry, notSelected);
                loopEntry = func_ov008_02054788(
                    context, currentGroup[itemIndex]);
                func_ov008_02054ba4(context, loopEntry, selected);
                ++itemIndex;
            } while (itemIndex < count);
        }
    }

    switch (selectedGroup) {
    case 0:
        selectedEntryId = func_ov008_02058c20(renderer);
        captionIndex = -1;
        break;
    case 1:
        entry = func_ov008_02054788(context, 10);
        func_ov008_02054b18(context, entry, renderer->entryHandle8c == 0);
        entry = func_ov008_02054788(context, 11);
        func_ov008_02054b18(context, entry, renderer->entryHandle90 == 0);
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

    entry = func_ov008_02054788(context, selectedEntryId);
    func_ov008_02054cc4(context, entry);
    renderer->activeEntryValue88 = entry->value0c;

    selectorEntry = func_ov008_02054788(context, 0x15);
    selectorPosition = func_ov008_02054820(context, selectorEntry);
    selectedPosition = func_ov008_02054820(context, entry);
    position.x = selectorPosition->x;
    position.y = selectedPosition->y;
    func_ov008_02054858(context, selectorEntry, &position);

    renderer->alternateGroupActive94 = selectedGroup != 0;
    if (captionIndex < 0) {
        return;
    }

    buffer = func_ov008_02055c84(renderer->variables04, captionIndex);
    func_02030158(renderer->surface4c);
    func_02030278(renderer->surface4c, 0x56, 0, 2, buffer, 1);
    func_020300f8(renderer->surface4c);
}
