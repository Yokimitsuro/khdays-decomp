typedef unsigned char u8;
#pragma opt_strength_reduction off
#pragma opt_common_subs off
#pragma opt_lifetimes off
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

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

extern s32 data_ov008_0208f050[];
extern u8 data_ov008_0208f080[];
extern u8 data_ov008_0208f090[];
extern u8 data_ov008_0208f0a0[];
extern u8 data_ov008_0208f0b0[];
extern u8 data_ov008_0208f0c0[];
extern u8 data_ov008_0208f0d0[];
extern u8 data_ov008_0208f0e0[];
extern u8 data_ov008_0208f0f0[];
extern u8 data_ov008_0208f100[];

extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void func_02035f84(void *tween);
extern s32 func_02023c40(void);
extern void func_020110f4(void *state);
extern void GFXi_SaveStateTo(void *state);
extern void func_02023c60(void *camera);
extern void *func_ov008_02050f08(u32 slot);
extern void func_0202a634(void *object, void *tag, int enabled, int kind);
extern void func_ov008_0205bb7c(void *object, int track);
extern void func_0202afc4(void *object, int enabled);
extern void func_0202afdc(void *object, u16 color);
extern u32 func_02016f10(void *dictionary, const void *name);
extern void func_ov008_0205bd50(void *out, u8 *resourceBase, u32 recordIndex);
extern u32 func_020235d0(u32 field, int kind);

void func_ov008_0205c010(Ov008MenuContext *menu, s32 nReserved)
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
    func_02035f84(context + 0x47d);
    func_02035f84(context + 0x484);
    func_02035f84(context + 0x48b);

    mode = func_02023c40();
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

    func_020110f4(context + 0x492);
    GFXi_SaveStateTo(context + 0x49c);
    func_02023c60(context + 1);

    tag = func_ov008_02050f08(2);
    func_0202a634(&menu->primaryWidget, tag, 1, 0xe);
    func_ov008_0205bb7c(&menu->primaryWidget, 0);
    tag = func_ov008_02050f08(0x40);
    func_0202a634(&menu->secondaryWidget, tag, 1, 0xe);
    func_ov008_0205bb7c(&menu->secondaryWidget, 0);

    i = 0;
    goto panel_loop_test;
panel_loop_body:
    {
        value = data_ov008_0208f050[i];
        if ((s32)value >= 0) {
            tag = func_ov008_02050f08(value);
            func_0202a634(&menu->panelWidgets[i], tag, 1, 0xe);
            func_ov008_0205bb7c(&menu->panelWidgets[i], 0);
            func_0202afc4(&menu->panelWidgets[i], 1);
            func_0202afdc(&menu->panelWidgets[i], 0x7fff);
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
        value = func_02016f10(dictionary, data_ov008_0208f0e0);
    }
    func_ov008_0205bd50(&menu->decodedTransforms[0], resourceBase, value);

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = func_02016f10(dictionary, data_ov008_0208f090);
    }
    func_ov008_0205bd50(&menu->decodedTransforms[1], resourceBase, value);

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = func_02016f10(dictionary, data_ov008_0208f0c0);
    }
    func_ov008_0205bd50(&menu->decodedTransforms[2], resourceBase, value);

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = func_02016f10(dictionary, data_ov008_0208f0b0);
    }
    func_ov008_0205bd50(&menu->decodedTransforms[3], resourceBase, value);

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = func_02016f10(dictionary, data_ov008_0208f100);
    }
    func_ov008_0205bd50(&menu->decodedTransforms[4], resourceBase, value);

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = func_02016f10(dictionary, data_ov008_0208f0d0);
    }
    func_ov008_0205bd50(&menu->decodedTransforms[5], resourceBase, value);

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = func_02016f10(dictionary, data_ov008_0208f080);
    }
    func_ov008_0205bd50(&menu->decodedTransforms[9], resourceBase, value);

    if (resourceBase != 0)
        dictionary = resourceBase + 0x40;
    else
        dictionary = 0;
    if (dictionary == 0) {
        value = 0xffffffff;
    } else {
        value = func_02016f10(dictionary, data_ov008_0208f0a0);
    }
    func_ov008_0205bd50(&menu->decodedTransforms[8], resourceBase, value);

    i = 0;
    goto transform_loop_test;
transform_loop_body:
    {
        if (data_ov008_0208f050[i] >= 0) {
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
        func_02035f84(&menu->panelBrightnessSlots[i]);
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
        value = func_02016f10(dictionary, data_ov008_0208f0f0);
    }
    func_ov008_0205bd50(&menu->decodedTransforms[12], resourceBase, value);

    value = func_020235d0(0, 9);
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

