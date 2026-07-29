typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov009SaveSlot {
    u16 profileValue;
    u16 cellCount;
    int gameValue8;
    int field40a;
    int gameValue0;
    int mappedResult;
    int hasCompleteData;
    int fieldC4b;
} Ov009SaveSlot;

typedef struct Ov009SaveContext {
    int variant;
    u8 pad004[0x04];
    int state;
    int result;
    u8 pad010[0x04];
    Ov009SaveSlot slots[3];
} Ov009SaveContext;

typedef struct Ov009GameState {
    int value0;
    int pad004;
    int value8;
    u8 pad00c[0xed4];
    u16 menuIds[1];
} Ov009GameState;

extern Ov009GameState *volatile data_0204be18;
extern void MI_CpuFill8(void *dst, unsigned char value, unsigned int size);
extern void NNS_FndInitList(void *list, int offset);
extern void func_ov009_02050754(void *state, void **callbacks);
extern void func_ov009_02050a5c(
    void *state,
    void *work,
    void *list,
    const u16 *ids
);
extern void func_ov009_020507e0(void *state, void *work, void *list);
extern void func_ov009_02050cac(void *state, void *work, void *list);
extern void WM_EndKeySharing_0x020507d4(void *state);
extern int func_020235d0(int field, int kind);

void func_ov009_02053554(Ov009SaveContext *ctx, int index, int result)
{
    char list[0x0c];
    char work[0x1e0];
    char state[0x100];
    Ov009SaveSlot *slot = &ctx->slots[index];

    MI_CpuFill8(slot, 0, sizeof(Ov009SaveSlot));

    switch (result) {
    case 0:
        slot->mappedResult = 1;
        break;
    case 2:
        slot->mappedResult = 0;
        break;
    case 4:
        slot->mappedResult = 2;
        break;
    default:
        slot->mappedResult = -1;
        break;
    }

    if (result != 0) {
        return;
    }

    NNS_FndInitList(list, 0x28);
    func_ov009_02050754(state, 0);
    func_ov009_02050a5c(state, work, list, data_0204be18->menuIds);
    func_ov009_020507e0(state, work, list);
    slot->cellCount = *(int *)(state + 0x78) + 1;
    func_ov009_02050cac(state, work, list);
    WM_EndKeySharing_0x020507d4(state);

    slot->gameValue8 = data_0204be18->value8;
    slot->profileValue = func_020235d0(0, 9);
    slot->gameValue0 = data_0204be18->value0;
    slot->field40a = func_020235d0(0x40a, 2);
    slot->fieldC4b = func_020235d0(0xc4b, 2);
    slot->hasCompleteData = func_020235d0(0x44e, 3) == 6;
}
