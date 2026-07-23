typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov000LoadEntry {
    u16 profileValue;
    u16 cellCount;
    int gameValue8;
    int field40a;
    int gameValue0;
    int mappedResult;
    int publishedResult;
    int hasCompleteData;
    int fieldC4b;
} Ov000LoadEntry;

typedef struct Ov000LoadSceneContext {
    u8 pad_0000[0x4b10];
    Ov000LoadEntry loadEntries[1];
} Ov000LoadSceneContext;

typedef struct Ov000GameState {
    int value0;
    int pad_0004;
    int value8;
    u8 pad_000c[0xed4];
    u16 menuIds[1];
} Ov000GameState;

extern Ov000LoadSceneContext *volatile data_ov000_0205ac24;
extern Ov000GameState *volatile data_0204be18;
extern void NNS_FndInitList(void *list, int offset);
extern void func_ov000_020582e0(void *state, int value);
extern void func_ov000_020585e8(
    void *state,
    void *work,
    void *list,
    const u16 *ids
);
extern void func_ov000_0205836c(void *state, void *work, void *list);
extern void func_ov000_02058838(void *state, void *work, void *list);
extern void WM_EndKeySharing_0x02058360(void *state);
extern int func_020235d0(int field, int kind);

void func_ov000_0204faf0(int index, int result) {
    char list[0xc];
    char work[0x1e0];
    char state[0x100];
    Ov000LoadEntry *entry =
        &data_ov000_0205ac24->loadEntries[index];

    switch (result) {
    case 0:
        entry->mappedResult = 1;
        break;
    case 2:
        entry->mappedResult = 0;
        break;
    case 4:
        entry->mappedResult = 2;
        break;
    default:
        entry->mappedResult = -1;
        break;
    }

    if (entry->publishedResult == -1) {
        entry->publishedResult = entry->mappedResult;
    }
    if (result != 0) {
        return;
    }

    NNS_FndInitList(list, 0x28);
    func_ov000_020582e0(state, 0);
    func_ov000_020585e8(state, work, list,
                        data_0204be18->menuIds);
    func_ov000_0205836c(state, work, list);
    entry->cellCount = *(int *)(state + 0x78) + 1;
    func_ov000_02058838(state, work, list);
    WM_EndKeySharing_0x02058360(state);

    entry->gameValue8 = data_0204be18->value8;
    entry->profileValue = func_020235d0(0, 9);
    entry->gameValue0 = data_0204be18->value0;
    entry->field40a = func_020235d0(0x40a, 2);
    entry->fieldC4b = func_020235d0(0xc4b, 2);
    entry->hasCompleteData = func_020235d0(0x44e, 3) == 6;
}
