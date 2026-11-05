/* Initialises the world map's panel context: clears its transforms and brightness tweens and
 * decodes the panel widgets' transforms and resources for the game mode. */

#pragma opt_strength_reduction off
#pragma opt_common_subs off
#pragma opt_lifetimes off

#include "nitro/types.h"

typedef struct Vec3 {
    u32 x;
    u32 y;
    u32 z;
} Vec3;

typedef struct Ov008DecodedTransform {
    u32 resourceIndex;
    Vec3 scale;
    u32 rotation[9];
    Vec3 translation;
} Ov008DecodedTransform;

typedef struct Ov008PanelWidget {
    u8 unknown00[0x24];
    u8 *resourceBase;
    u8 unknown28[0x7c];
    Vec3 translation;
    Vec3 scale;
    u8 unknownbc[0x4c];
} Ov008PanelWidget;

typedef struct Ov008PanelBrightnessSlot {
    u8 tween[0x1c];
    s32 currentBrightness;
} Ov008PanelBrightnessSlot;

typedef struct Ov008MenuContext {
    u8 unknown0000[0x3c];
    Ov008DecodedTransform decodedTransforms[13];
    u8 unknown037c[4];
    Ov008PanelWidget primaryWidget;
    Ov008PanelWidget secondaryWidget;
    Ov008PanelWidget panelWidgets[12];
    u8 unknown11f0[0x88];
    Ov008PanelBrightnessSlot panelBrightnessSlots[12];
} Ov008MenuContext;

extern s32 data_ov025_020b3bb0[];
extern u8 gOv025Dummy09Name[];
extern u8 gOv025Dummy01Name[];
extern u8 gOv025Dummy08Name[];
extern u8 gOv025Dummy03Name[];
extern u8 gOv025Dummy02Name[];
extern u8 gOv025Dummy05Name[];
extern u8 gOv025Dummy00Name[];
extern u8 gOv025Dummy12Name[];
extern u8 gOv025Dummy04Name[];

extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void Tween_Clear(void *tween);
extern s32 GetFrameRateMode(void);
extern void NNS_GfdGetFrmTexVramState(void *state);
extern void GFXi_SaveStateTo(void *state);
extern void Projection_LoadDefaults(void *camera);
extern void *Ov025_PackSlotTag(u32 slot);
extern void RegisterSeqAndInit(void *object, void *tag, int enabled, int kind);
extern void Ov025_BindUiAnimTracks(void *object, int track);
extern void SceneNode_SetFlag40(void *object, int enabled);
extern void Widget_SetTagWord(void *object, u16 color);
extern u32 NNS_G3dGetResDictIdxByName(void *dictionary, const void *name);
extern void Ov025_DecodeResourceTransform(void *out, u8 *resourceBase, u32 recordIndex);
extern u32 GameState_GetField(u32 field, int kind);

void Ov025_WorldMap_InitPanelContext(Ov008MenuContext *menu, s32 nReserved)
{
    u32 *context;
    s32 mode;
    void *tag;
    u8 *dictionary;
    u32 value;
    u32 value2;
    u8 *resourceBase;
    s32 i;

    context = (u32 *)menu;
    MI_CpuFill8(context, 0, 0x13f8);
    context[0x47c] = 0xffffffff;
    Tween_Clear(context + 0x47d);
    Tween_Clear(context + 0x484);
    Tween_Clear(context + 0x48b);

    mode = GetFrameRateMode();
    switch (mode) {
    case 0:
        context[0] = 0x1000;
        break;
    case 1:
        context[0] = 0xaaa;
        break;
    case 2:
        context[0] = 0x2000;
        break;
    }

    NNS_GfdGetFrmTexVramState(context + 0x492);
    GFXi_SaveStateTo(context + 0x49c);
    Projection_LoadDefaults(context + 1);

    tag = Ov025_PackSlotTag(2);
    RegisterSeqAndInit(&menu->primaryWidget, tag, 1, 0xe);
    Ov025_BindUiAnimTracks(&menu->primaryWidget, 0);
    tag = Ov025_PackSlotTag(0x40);
    RegisterSeqAndInit(&menu->secondaryWidget, tag, 1, 0xe);
    Ov025_BindUiAnimTracks(&menu->secondaryWidget, 0);

    i = 0;
    goto panel_loop_test;
panel_loop_body:
    {
        value = data_ov025_020b3bb0[i];
        if ((s32)value >= 0) {
            tag = Ov025_PackSlotTag(value);
            RegisterSeqAndInit(&menu->panelWidgets[i], tag, 1, 0xe);
            Ov025_BindUiAnimTracks(&menu->panelWidgets[i], 0);
            SceneNode_SetFlag40(&menu->panelWidgets[i], 1);
            Widget_SetTagWord(&menu->panelWidgets[i], 0x7fff);
        }
        i++;
    }
panel_loop_test:
    if (i < 12)
        goto panel_loop_body;

    resourceBase = menu->primaryWidget.resourceBase;

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = NNS_G3dGetResDictIdxByName(dictionary, gOv025Dummy00Name);
    }
    Ov025_DecodeResourceTransform(&menu->decodedTransforms[0], resourceBase, value);

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = NNS_G3dGetResDictIdxByName(dictionary, gOv025Dummy01Name);
    }
    Ov025_DecodeResourceTransform(&menu->decodedTransforms[1], resourceBase, value);

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = NNS_G3dGetResDictIdxByName(dictionary, gOv025Dummy02Name);
    }
    Ov025_DecodeResourceTransform(&menu->decodedTransforms[2], resourceBase, value);

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = NNS_G3dGetResDictIdxByName(dictionary, gOv025Dummy03Name);
    }
    Ov025_DecodeResourceTransform(&menu->decodedTransforms[3], resourceBase, value);

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = NNS_G3dGetResDictIdxByName(dictionary, gOv025Dummy04Name);
    }
    Ov025_DecodeResourceTransform(&menu->decodedTransforms[4], resourceBase, value);

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = NNS_G3dGetResDictIdxByName(dictionary, gOv025Dummy05Name);
    }
    Ov025_DecodeResourceTransform(&menu->decodedTransforms[5], resourceBase, value);

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = NNS_G3dGetResDictIdxByName(dictionary, gOv025Dummy09Name);
    }
    Ov025_DecodeResourceTransform(&menu->decodedTransforms[9], resourceBase, value);

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = NNS_G3dGetResDictIdxByName(dictionary, gOv025Dummy08Name);
    }
    Ov025_DecodeResourceTransform(&menu->decodedTransforms[8], resourceBase, value);

    i = 0;
    goto transform_loop_test;
transform_loop_body:
    {
        if (data_ov025_020b3bb0[i] >= 0) {
            menu->panelWidgets[i].scale = menu->decodedTransforms[i].scale;
            menu->panelWidgets[i].translation =
                menu->decodedTransforms[i].translation;
        }
        i++;
    }
transform_loop_test:
    if (i < 12)
        goto transform_loop_body;

    i = 0;
    goto brightness_loop_test;
brightness_loop_body:
    {
        menu->panelBrightnessSlots[i].currentBrightness = 0x1000;
        Tween_Clear(&menu->panelBrightnessSlots[i]);
        i++;
    }
brightness_loop_test:
    if (i < 12)
        goto brightness_loop_body;

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = NNS_G3dGetResDictIdxByName(dictionary, gOv025Dummy12Name);
    }
    Ov025_DecodeResourceTransform(&menu->decodedTransforms[12], resourceBase, value);

    value = GameState_GetField(0, 9);
    value2 = 0;
    if ((s32)value >= 0x5e) {
        value2 += 0x400;
    }
    if ((s32)value >= 0xc1) {
        value2 += 0x400;
    }
    if ((s32)value >= 0x12b) {
        value2 += 0x400;
    }
    if ((s32)value >= 0x160) {
        value2 += 0x400;
    }
    context[0xd0] = value2;
    context[0xd1] = value2;
    context[0xd2] = value2;
    menu->secondaryWidget.scale = menu->decodedTransforms[12].scale;
    menu->secondaryWidget.translation = menu->decodedTransforms[12].translation;
}

