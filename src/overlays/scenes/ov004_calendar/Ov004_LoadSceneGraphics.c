/* Loads the calendar's graphics: the ten digit models, the camera, the sprites, the label text
 * renderer and the palette. */

#include "nitro/types.h"

typedef struct Fx32Pair {
    int x;
    int y;
} Fx32Pair;

typedef struct SpriteManagerInit {
    void *resource;
    int enabled;
    int reserved0;
    int reserved1;
} SpriteManagerInit;

typedef struct Ov004Context {
    u8 pad_0000[0x5544];
    void *objects[3];
} Ov004Context;

extern Ov004Context *data_ov004_02051384;
extern void *data_ov004_02051300[];
extern char gOv004UiCalClHrtPath[];
extern char gOv004TextFontEu10AllPath[];
extern char data_ov004_020510b0[];

extern void RegisterSeqAndInit(void *object, void *resource, int mode, int style);
extern void SceneNode_SetFlag40(void *object, int enabled);
extern void Ov004_LayoutRollingDigits(int valueFx12);
extern void Projection_LoadDefaults(void *object);
extern void ObjNode_InitFromDesc(void *manager, SpriteManagerInit *init);
extern void *VeneerTo_SlotTable_AddEntry(void *manager, int index, int arg);
extern void SlotTable_SetEntryPriority(void *manager, void *object, int arg);
extern void Slot_SetPosition(void *manager, void *object, Fx32Pair *position);
extern void Slot_ClearFlagBit1(void *manager, void *object);
extern void SlotTable_SetEntryPair(void *manager, void *object, int arg, int scale);
extern void SlotTable_SetEntryFlag(void *manager, void *object, int arg);
extern void SlotTable_SetBlendAlpha(void *manager, int value);
extern void SlotTable_SetMode(void *manager, int enabled);
extern void ClampToRange0to16At0x4628(void *manager, int value);
extern void Font_LoadUTF16(void *textEngine, void *resource);
extern void TileTextRenderer_Init(void *tileEngine, int layer, void *textEngine, u16 *rect);
extern void GX_LoadBGPltt(void *src, int offset, u32 size);

void Ov004_LoadSceneGraphics(void) {
    Fx32Pair position;
    SpriteManagerInit init;
    u16 rect[8];
    int i;
    int offset;
    void *object;

    i = 0;
    offset = i;
    for (; i < 10; i++) {
        RegisterSeqAndInit((char *)data_ov004_02051384 + offset,
                      data_ov004_02051300[i], 0, 14);
        SceneNode_SetFlag40((char *)data_ov004_02051384 + offset, 1);
        offset += 0x108;
    }

    Ov004_LayoutRollingDigits(*(int *)((char *)data_ov004_02051384 + 0x5568));
    Projection_LoadDefaults((char *)data_ov004_02051384 + 0xac0);
    *(int *)((char *)data_ov004_02051384 + 0x55ec) = 0;

    init.resource = gOv004UiCalClHrtPath;
    init.enabled = 1;
    init.reserved0 = 0;
    init.reserved1 = 0;
    ObjNode_InitFromDesc((char *)data_ov004_02051384 + 0xb0c, &init);

    for (i = 0; i < 3; i++) {
        object = VeneerTo_SlotTable_AddEntry((char *)data_ov004_02051384 + 0xb0c, i, 0);
        data_ov004_02051384->objects[i] = object;
        SlotTable_SetEntryPriority((char *)data_ov004_02051384 + 0xb0c,
                      data_ov004_02051384->objects[i], 0);

        switch (i) {
        case 0:
            position.x = 0x80000;
            position.y = 0x78000;
            *(int *)((char *)data_ov004_02051384 + 0x5588) = 0x78000;
            Slot_SetPosition((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i],
                          &position);
            Slot_ClearFlagBit1((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i]);
            SlotTable_SetEntryFlag((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i], 0);
            break;
        case 1:
            position.x = 0x80000;
            position.y = 0x60000;
            *(int *)((char *)data_ov004_02051384 + 0x557c) = 0;
            *(int *)((char *)data_ov004_02051384 + 0x5580) = 0x171;
            Slot_SetPosition((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i],
                          &position);
            SlotTable_SetEntryPair((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i],
                          *(int *)((char *)data_ov004_02051384 + 0x557c), 0x1000);
            SlotTable_SetEntryFlag((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i], 0);
            break;
        case 2:
            position.x = 0x64000;
            position.y = 0x58000;
            Slot_SetPosition((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i],
                          &position);
            SlotTable_SetEntryFlag((char *)data_ov004_02051384 + 0xb0c,
                          data_ov004_02051384->objects[i], 0);
            break;
        }
    }

    SlotTable_SetBlendAlpha((char *)data_ov004_02051384 + 0xb0c, 0x2f);
    SlotTable_SetMode((char *)data_ov004_02051384 + 0xb0c, 1);
    ClampToRange0to16At0x4628((char *)data_ov004_02051384 + 0xb0c, 0);

    Font_LoadUTF16((char *)data_ov004_02051384 + 0x55a0, gOv004TextFontEu10AllPath);

    rect[0] = 0;
    rect[4] = 0;
    rect[5] = 0;
    rect[6] = 0;
    rect[7] = 0;
    rect[1] = 11;
    rect[2] = 0x20;
    rect[3] = 6;
    TileTextRenderer_Init((char *)data_ov004_02051384 + 0x55ac, 3,
                  (char *)data_ov004_02051384 + 0x55a0, rect);

    GX_LoadBGPltt(data_ov004_020510b0, 0, 8);
}
