typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u8 pad_00[0x10];
    u32 nCharSize;
    void *pCharData;
} CharacterData;

typedef struct {
    void *pScreen;
    CharacterData *pChar;
    void *pPalette;
} SpriteResSet;

typedef struct {
    u32 resourceArchiveEntry;
    u8 pad_0004[0x94e8];
    int loadedPortraitIndex;
    int selectedPortraitIndex;
    int currentState;
} CharacterSelectContext;

extern CharacterSelectContext *data_ov006_02056664;
extern void *func_0201ef9c(u32 archiveEntry, int mode);
extern void func_02024c94(SpriteResSet *resources, void *archive,
                          int screenIndex, int characterIndex,
                          int paletteIndex);
extern void GX_LoadBG0Char(void *source, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void func_ov006_02053cdc(u32 cellTag, int x, int y);

void func_ov006_02053d54(void)
{
    CharacterSelectContext *context = data_ov006_02056664;
    void *portraitArchive;
    SpriteResSet resources;
    int characterResourceIndex;
    u32 portraitCellTag;

    if (context == 0) {
        return;
    }

    switch (context->currentState) {
    case 0:
    case 1:
    case 2:
    case 3:
        goto done;
    case 4:
    case 5:
    case 6:
        break;
    default:
        goto done;
    }

    if (context->loadedPortraitIndex == context->selectedPortraitIndex) {
        return;
    }

    portraitArchive = func_0201ef9c(
        (((context->resourceArchiveEntry + 0x8000) & 0xfffffc) << 7) |
            0x80000000,
        0xe);

    switch (data_ov006_02056664->selectedPortraitIndex) {
    case 0:
    case 1:
    case 2:
    case 3:
        characterResourceIndex = 4;
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        characterResourceIndex = 5;
        break;
    case 8:
    case 9:
    case 10:
    case 11:
        characterResourceIndex = 6;
        break;
    case 12:
    case 13:
    case 14:
    case 15:
        characterResourceIndex = 7;
        break;
    case 16:
    case 17:
    case 18:
    default:
        characterResourceIndex = 8;
        break;
    }

    func_02024c94(
        &resources, portraitArchive, -1, characterResourceIndex, -1);
    GX_LoadBG0Char(
        resources.pChar->pCharData, 0, resources.pChar->nCharSize);
    if (portraitArchive != 0) {
        NNSi_FndFreeFromDefaultHeap(portraitArchive);
    }

    switch (data_ov006_02056664->selectedPortraitIndex) {
    case 0:
        portraitCellTag = 6;
        break;
    case 1:
        portraitCellTag = 7;
        break;
    case 2:
        portraitCellTag = 8;
        break;
    case 3:
        portraitCellTag = 9;
        break;
    case 4:
        portraitCellTag = 10;
        break;
    case 5:
        portraitCellTag = 11;
        break;
    case 6:
        portraitCellTag = 12;
        break;
    case 7:
        portraitCellTag = 13;
        break;
    case 8:
        portraitCellTag = 14;
        break;
    case 9:
        portraitCellTag = 15;
        break;
    case 10:
        portraitCellTag = 16;
        break;
    case 11:
        portraitCellTag = 17;
        break;
    case 12:
        portraitCellTag = 18;
        break;
    case 13:
        portraitCellTag = 19;
        break;
    case 14:
        portraitCellTag = 20;
        break;
    case 15:
        portraitCellTag = 21;
        break;
    case 16:
        portraitCellTag = 22;
        break;
    case 17:
        portraitCellTag = 23;
        break;
    case 18:
        portraitCellTag = 24;
        break;
    default:
        portraitCellTag = 25;
        break;
    }

    func_ov006_02053cdc(portraitCellTag, 0, 5);
    data_ov006_02056664->loadedPortraitIndex =
        data_ov006_02056664->selectedPortraitIndex;
done:
    return;
}