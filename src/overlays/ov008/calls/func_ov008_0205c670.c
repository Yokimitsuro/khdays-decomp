/* Advance or finish the main-menu info-window position transition. */
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

typedef struct Ov008InfoWindowPositionState {
    u32 currentX;
    s32 targetX;
    u16 windowControl;
    u16 padding0a;
} Ov008InfoWindowPositionState;

typedef struct Ov008InfoWindowRow {
    short verticalOffset;
    char unknown02[0x26];
} Ov008InfoWindowRow;

typedef struct Ov008InfoWindowUpdateContext {
    char unknown0000[0x1c];
    s32 pendingDisplayMode;
    char unknown0020[0x1c];
    s32 infoWindowUpdatePending;
    char unknown0040[0x328];
    Tween infoWindowTween;
    Ov008InfoWindowPositionState infoWindowPosition;
    char unknown0390[0x135c];
    Ov008InfoWindowRow infoWindowRows[8];
} Ov008InfoWindowUpdateContext;

extern Ov008InfoWindowUpdateContext *func_ov008_02050cd4(void);
extern void func_ov008_0205c5f0(u32 horizontalOffset, u16 windowControl);
extern void func_0203602c(Tween *tween, s32 *value);

int func_ov008_0205c670(void)
{
    Ov008InfoWindowUpdateContext *context;

    context = func_ov008_02050cd4();
    if (context->pendingDisplayMode >= 0) {
        volatile u32 *displayControl;

        displayControl = (volatile u32 *)0x04000000;
        *displayControl = (*displayControl & 0xffff1fff) |
                          ((u32)context->pendingDisplayMode << 13);
        context->pendingDisplayMode = -1;
    }

    if (context->infoWindowUpdatePending != 0) {
        if (context->infoWindowTween.flags.finished != 0) {
            u32 currentX;

            currentX = context->infoWindowPosition.currentX;
            if (currentX != 0x7fffffff ||
                context->infoWindowPosition.targetX != 0x7fffffff) {
                if (currentX != 0x7fffffff) {
                    func_ov008_0205c5f0(
                        currentX, context->infoWindowPosition.windowControl);
                }
                context->infoWindowPosition.currentX =
                    context->infoWindowPosition.targetX;
                context->infoWindowPosition.targetX = 0x7fffffff;
            }
        } else {
            s32 sampledX;
            int i;

            func_0203602c(&context->infoWindowTween, &sampledX);
            if (context->infoWindowPosition.currentX != 0x7fffffff) {
                func_ov008_0205c5f0(
                    context->infoWindowPosition.currentX,
                    context->infoWindowPosition.windowControl);
            }
            context->infoWindowPosition.currentX =
                context->infoWindowPosition.targetX;
            context->infoWindowPosition.targetX = sampledX >> 12;
            for (i = 0; i < 8; i++) {
                context->infoWindowRows[i].verticalOffset =
                    0x6a - context->infoWindowPosition.targetX;
            }
        }
        context->infoWindowUpdatePending = 0;
    }
    return 1;
}
