/* Ticks the sub-menu; on result 4 rebuilds the logo, on 5 starts the transition out. */

#include "nitro/types.h"

typedef void (*OverlayCallback)(void);

typedef struct {
    int state_0;
    u8 pad_0004[8];
    u8 update_object[0x4bdc];
    u8 overlay_image[0x58];
    int transition_flag;
    u8 pad_4c44[0x42c];
    int sharing_handle;
    int sharing_state;
} OverlayContext;

extern OverlayContext *NNSi_FndGetCurrentRootHeap(void);
extern void KeyRepeat_Step(void *image);
extern unsigned short Mem_ReadU16(void *image);
extern void Ov000_SetSubSceneHalf1C(int);
extern void Scene_DrawNode(void *object);
extern int Ov000_GetSubSceneResult(void);
extern void VeneerTo_Obj_Destroy(int handle);
extern void Ov000_PreloadLogoResources(void);
extern void Ov000_Title_CreateLogoObjects(void);
extern void Ov000_ReleaseLogoResources(void);
extern void StampByteAndInvokeSubStructAt(int first, int second);
extern void Table_TailCallWithEntry(int first, int second);
extern void Ov000_ReentryState(void);
extern void Ov000_TickBootFadeTransition(void);

OverlayCallback Ov000_WaitSubMenuResult(void) {
    OverlayContext *context = NNSi_FndGetCurrentRootHeap();

    KeyRepeat_Step(context->overlay_image);
    Ov000_SetSubSceneHalf1C(Mem_ReadU16(context->overlay_image));
    Scene_DrawNode(context->update_object);

    switch (Ov000_GetSubSceneResult()) {
    case 4:
        VeneerTo_Obj_Destroy(context->sharing_handle);
        context->sharing_handle = context->sharing_state = 0;
        Ov000_PreloadLogoResources();
        Ov000_Title_CreateLogoObjects();
        Ov000_ReleaseLogoResources();
        return Ov000_ReentryState;
    case 5:
        context->state_0 = 0;
        context->transition_flag = 1;
        StampByteAndInvokeSubStructAt(1, 3);
        Table_TailCallWithEntry(0, 30);
        return Ov000_TickBootFadeTransition;
    default:
        return 0;
    }
}
