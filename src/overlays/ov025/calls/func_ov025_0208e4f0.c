typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct TweenFlags {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
    u32 reserved : 29;
} TweenFlags;

typedef struct Tween {
    s32 mode;
    s32 duration;
    s32 from;
    s32 to;
    long long startTick;
    TweenFlags flags;
} Tween;

typedef struct Ov008PanelWidget {
    char data[0x108];
} Ov008PanelWidget;

typedef struct Ov008PanelBrightnessSlot {
    Tween tween;
    s32 currentBrightness;
} Ov008PanelBrightnessSlot;

typedef struct Ov008MenuContext {
    char unknown0000[0x590];
    Ov008PanelWidget panelWidgets[12];
    char unknown11f0[0x88];
    Ov008PanelBrightnessSlot panelBrightnessSlots[12];
} Ov008MenuContext;

extern s32 data_ov025_020b3bb0[];
extern void func_0203602c(Tween *tween, s32 *value);
extern void func_0202afdc(void *widget, u16 color);

/* Ov008_UpdatePanelBrightnessTweens
 * Samples unfinished per-panel tweens and applies the resulting RGB555
 * grayscale color before the twelve panel widgets are rendered. */
void func_ov025_0208e4f0(Ov008MenuContext *context)
{
    u16 i;

    i = 0;
    do {
        if (data_ov025_020b3bb0[i] >= 0) {
            Ov008PanelBrightnessSlot *slot;

            slot = &context->panelBrightnessSlots[i];
            if (slot->tween.flags.finished == 0) {
                s32 brightness;
                s32 shade;

                func_0203602c(&slot->tween, &brightness);
                shade = (s32)(((long long)brightness * 31 + 0x800) >> 12);
                func_0202afdc(
                    &context->panelWidgets[i],
                    (u16)(shade | (shade << 5) | (shade << 10)));
                context->panelBrightnessSlots[i].currentBrightness = brightness;
            }
        }
        i = (u16)(i + 1);
    } while (i < 12);
}

