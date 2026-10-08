/* Fades both screens to white and moves to closing the ov106 scene, clearing game-state
 * field 0x20e6. */

#include "nitro/types.h"
#include "game/engine.h"

typedef void *(*Ov022StateCallback)(void);

typedef struct Ov022Context {
    u16 flags;
    char pad_0002[0x1a];
    int brightnessMain;
    int brightnessSub;
} Ov022Context;

extern u8 data_0204be04;
extern Ov022Context *data_ov022_020b2e60;

extern void Ov022_UpdateCameraAndViews(int mode);
extern void *Ov022_StateCloseOv106Scene(void);

Ov022StateCallback Ov022_StateReturnToHub(void)
{
    Ov022Context *context = data_ov022_020b2e60;
    Ov022StateCallback next = 0;

    if (data_0204be04 != 0) {
        return next;
    }

    Ov022_UpdateCameraAndViews(1);

    int completed = 0;

    context->brightnessMain += GetFrameRateMode() == 1 ? 0x2000 : 0x1800;
    if (context->brightnessMain >= 0x10000) {
        context->brightnessMain = 0x10000;
        completed = 1;
    }
    context->brightnessSub = context->brightnessMain;

    if (completed != 0) {
        StoreToGlobalPtr4Field28(1);
        next = Ov022_StateCloseOv106Scene;
        GameState_SetField(0x20e6, 1, 0);
    }

    SetMasterBrightnessMain(context->brightnessMain >> 12);
    SetMasterBrightnessSub(context->brightnessSub >> 12);
    return next;
}
