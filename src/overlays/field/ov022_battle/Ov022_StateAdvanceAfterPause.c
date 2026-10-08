/* Fades both screens out (or waits for the scene when not fading) and moves to closing the ov106
 * scene. */

#include "nitro/types.h"
#include "game/engine.h"

typedef void *(*Ov022StateCallback)(void);

typedef struct Ov022Context {
    u16 flags;
    char pad_0002[0x1a];
    int brightnessMain;
    int brightnessSub;
    char pad_0024[0x1a];
    s8 state;
} Ov022Context;

extern u8 data_0204be04;
extern Ov022Context *data_ov022_020b2e60;

extern void Ov022_UpdateCameraAndViews(int mode);
extern int Ov002_Scene_IsIdle(void);
extern void *Ov022_StateCloseOv106Scene(void);

Ov022StateCallback Ov022_StateAdvanceAfterPause(void)
{
    Ov022Context *context = data_ov022_020b2e60;
    Ov022StateCallback next = 0;

    if (data_0204be04 != 0) {
        return next;
    }

    Ov022_UpdateCameraAndViews(1);
    if (context->state != 0) {
        if (context->state == 2 && Ov002_Scene_IsIdle() != 0) {
            StoreToGlobalPtr4Field28(1);
            next = Ov022_StateCloseOv106Scene;
        }
    } else {
        context->brightnessMain -= GetFrameRateMode() == 1 ? 0x3000 : 0x2000;
        context->brightnessSub -= GetFrameRateMode() == 1 ? 0x3000 : 0x2000;

        u8 completed = 0;

        if (context->brightnessMain <= -0x10000) {
            context->brightnessMain = -0x10000;
            completed++;
        }
        if (context->brightnessSub <= -0x10000) {
            context->brightnessSub = -0x10000;
            completed++;
        }

        if (completed >= 2 && Ov002_Scene_IsIdle() != 0) {
            StoreToGlobalPtr4Field28(1);
            next = Ov022_StateCloseOv106Scene;
        }

        SetMasterBrightnessMain(context->brightnessMain >> 12);
        SetMasterBrightnessSub(context->brightnessSub >> 12);
    }

    return next;
}
