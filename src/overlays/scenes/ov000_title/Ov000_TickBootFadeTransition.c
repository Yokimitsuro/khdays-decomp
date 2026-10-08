/* Per-frame boot-scene transition tick: recomputes scroll bounds and the render node every frame,
 * then drives a fade keyed off context->frame -- ramping brightness up through frame 0x20, holding,
 * and from 0x28 ramping down while adjusting both screens' blend brightness, clearing the blend
 * registers past 0x30. */

#include "nitro/types.h"
#include "game/engine.h"

typedef void (*Ov000StateFn)(void);

typedef struct Ov000BootContext {
    int frame;
    u8 pad_0004[8];
    u8 renderNode[0x108];
    u8 scrollBounds[0x4b19];
    s8 transitionMode;
    u8 pad_4c2e[0x43e];
    void *pSceneObject;
    void *pAuxObject;
} Ov000BootContext;

extern Ov000BootContext *NNSi_FndGetCurrentRootHeap(void);
extern void Ov000_FadeStateHookNoOp(void);
extern void Camera_CommitMatricesEx(void *bounds, int right, int left, int top,
                          int bottom);
extern void Scene_DrawNode(void *renderNode);
extern void G2x_SetBlendBrightness_(u32 registerAddress, int planeMask,
                                    int brightness);
extern void Table_TailCallWithEntry(int first, int second);
extern void VeneerTo_Obj_Destroy(void *handle);
extern void Ov000_BootDispatch(void);

Ov000StateFn Ov000_TickBootFadeTransition(void) {
    Ov000BootContext *context = NNSi_FndGetCurrentRootHeap();

    Ov000_FadeStateHookNoOp();
    Camera_CommitMatricesEx(context->scrollBounds, 0x3b33, -0x3b33,
                  -0x4d9a, 0x4d9a);
    Scene_DrawNode(context->renderNode);

    if (context->frame <= 0x20) {
        SetMasterBrightnessMain(context->frame / 2);
        SetMasterBrightnessSub(context->frame / 2);
    } else if (context->frame < 0x28) {
        *(volatile u32 *)0x04001000 =
            *(volatile u32 *)0x04001000 & ~0x1f00 | 0x1200;
    } else if (context->frame < 0x30) {
        G2x_SetBlendBrightness_(0x04000050, 3, 0x10);
        G2x_SetBlendBrightness_(0x04001050, 0x12, 0x10);
        SetMasterBrightnessMain((-(context->frame - 0x28)) << 1);
        SetMasterBrightnessSub((-(context->frame - 0x28)) << 1);
    } else {
        *(volatile u16 *)0x04000050 = 0;
        *(volatile u16 *)0x04001050 = 0;
        SetMasterBrightnessMain(-0x10);
        SetMasterBrightnessSub(-0x10);

        if (context->frame == 0x30) {
            Table_TailCallWithEntry(1, 0x10);
        }

        if (SoundStrm_HasPlaybackPos(1) == 0) {
            context->frame = 0;
            switch (context->transitionMode) {
            case 0:
                if (context->pSceneObject != 0) {
                    VeneerTo_Obj_Destroy(context->pSceneObject);
                    context->pSceneObject = 0;
                }
                break;
            case 1:
            case 2:
                if (context->pSceneObject != 0) {
                    VeneerTo_Obj_Destroy(context->pSceneObject);
                    context->pSceneObject = 0;
                }
                if (context->pAuxObject != 0) {
                    VeneerTo_Obj_Destroy(context->pAuxObject);
                    context->pAuxObject = 0;
                }
                break;
            }
            return Ov000_BootDispatch;
        }
    }

    context->frame++;
    return 0;
}
