typedef unsigned char u8;
typedef unsigned int  u32;

typedef struct Ov009MenuContext {
    u8 pad_0000[0x95d4];
    int brightness;
    u8 brightnessTween[0x18];
    u32 field_95f0_bits_0_1 : 2;
    u32 skipBrightnessUpdate : 1;
    u32 field_95f0_bits_3_31 : 29;
    int field_95f4;
    int mirrorSubBrightness;
    u8 pad_95fc[0x9660 - 0x95fc];
    u8 activeWidgetList[1];
} Ov009MenuContext;

typedef struct Ov009Widget {
    int (*update)(void);
} Ov009Widget;

extern Ov009MenuContext *volatile data_ov009_020563e4[];

#define OV009_CONTEXT (data_ov009_020563e4[1])

extern void  CP_SaveContext(void *context);
extern void  CPi_RestoreContext(const void *context);
extern void  func_0203602c(void *tween, int *value);
extern int   func_ov009_0204cb84(void);
extern void  func_0201e3cc(int brightness);
extern void  func_0201e374(int brightness);
extern void *NNS_FndGetNextListObject(void *list, void *previous);
extern void  func_ov009_0204e4c0(void *widget);

static volatile unsigned short *const REG_DIVCNT =
    (volatile unsigned short *)0x04000280;

void func_ov009_0204cd7c(void)
{
    u32 cpContext[7];
    int brightness;
    Ov009Widget *widget;
    Ov009Widget *next;

    OV009_CONTEXT->field_95f4 = 0;

    if (OV009_CONTEXT->skipBrightnessUpdate == 0) {
        CP_SaveContext(cpContext);
        {
            Ov009MenuContext *context = OV009_CONTEXT;
            func_0203602c(
                context->brightnessTween,
                &context->brightness);
        }
        CPi_RestoreContext(cpContext);

        while ((*REG_DIVCNT & 0x8000) != 0) {
        }

        brightness = OV009_CONTEXT->brightness >> 12;
        if (func_ov009_0204cb84() == 6 ||
            func_ov009_0204cb84() == 7) {
            func_0201e3cc(brightness);
        } else {
            if (OV009_CONTEXT->mirrorSubBrightness != 0) {
                func_0201e3cc(brightness);
            }
            func_0201e374(brightness);
        }
    }

    widget = NNS_FndGetNextListObject(
        OV009_CONTEXT->activeWidgetList, 0);
    if (widget == 0) {
        return;
    }

    do {
        next = NNS_FndGetNextListObject(
            OV009_CONTEXT->activeWidgetList, widget);
        if (widget->update() == 0) {
            func_ov009_0204e4c0(widget);
        }
        widget = next;
    } while (next != 0);
}
