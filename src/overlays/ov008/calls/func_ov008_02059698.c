typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    int x;
    int y;
} UiLayoutPos;

typedef struct {
    u8 pad00[0x0c];
    int value0c;
} Ov008MenuEntry;

typedef struct {
    u8 pad00[4];
    u8 variables04[0x48];
    u8 surface4c[0x3c];
    int activeEntryValue88;
    u8 pad8c[0x538];
    u16 icon5c4;
} Ov008MenuPageState;

extern int func_ov008_02050cd4(void);
extern int func_ov008_02050c54(void);
extern Ov008MenuEntry *func_ov008_02054788(int context, int entryId);
extern UiLayoutPos *func_ov008_02054820(int context, Ov008MenuEntry *entry);
extern void func_ov008_02054858(int context, Ov008MenuEntry *entry,
                                UiLayoutPos *position);
extern void func_02033b78(unsigned int soundId, unsigned int variant);
extern int func_ov008_02057328(int value);
extern void *func_ov008_02055c84(void *variables, int index);
extern void func_02030158(void *surface);
extern void func_02030278(void *surface, int id, int x, int y,
                          void *buffer, int shadow);
extern void func_020300f8(void *surface);

void func_ov008_02059698(Ov008MenuEntry *selectedEntry, u32 eventFlags)
{
    int context;
    Ov008MenuEntry *selectorEntry;
    int renderer;
    UiLayoutPos *selectorPosition;
    UiLayoutPos *selectedPosition;
    void *buffer;
    int previousValue;
    int icon;
    UiLayoutPos position;

    renderer = func_ov008_02050cd4();
    if ((eventFlags & 0xf0) == 0) {
        return;
    }

    context = func_ov008_02050c54();
    selectorEntry = func_ov008_02054788(context, 0x15);
    selectorPosition = func_ov008_02054820(context, selectorEntry);
    selectedPosition = func_ov008_02054820(context, selectedEntry);
    if ((u32)(selectedEntry->value0c - 7) <= 1) {
        position.x = selectedPosition->x - 0x30000;
        position.y = selectedPosition->y;
    } else {
        position.x = selectorPosition->x;
        position.y = selectedPosition->y;
    }
    func_ov008_02054858(context, selectorEntry, &position);

    previousValue = *(int *)(renderer + 0x88);
    if (previousValue != -1 && previousValue != selectedEntry->value0c) {
        func_02033b78(0, 0);
    }
    *(int *)(renderer + 0x88) = selectedEntry->value0c;

    icon = func_ov008_02057328(selectedEntry->value0c);
    if (icon >= 0) {
        *(u16 *)(renderer + 0x5c4) = (u16)icon;
    }
    if (icon < 0) {
        return;
    }
    buffer = func_ov008_02055c84((void *)(renderer + 4), icon);
    func_02030158((void *)(renderer + 0x4c));
    func_02030278((void *)(renderer + 0x4c), 0x56, 0, 2, buffer, 1);
    func_020300f8((void *)(renderer + 0x4c));
}
