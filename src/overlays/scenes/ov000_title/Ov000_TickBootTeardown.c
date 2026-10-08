/* Boot teardown step: updates the key repeat, draws the logo, and when loading ends either records
 * the saved scene and builds the title logo, or starts the fade to the next scene. */

#include "nitro/types.h"

typedef void (*Ov000StateFn)(void);

typedef struct Ov000BootContext {
    int frame;
    u8 pad_0004[8];
    u8 renderNode[0x108];
    u8 scrollBounds[0x9c];
    u8 pad_01b0[0x4a38];
    u8 overlayImage[0x47];
    u8 resumeBoot;
    u8 pad_4c30[0x10];
    int transitionFlag;
    u8 pad_4c44[0xf];
    u8 savedSceneFlag;
    int savedSceneId;
    u8 pad_4c58[0x414];
    void *pSceneObject;
    u8 pad_5070[4];
    void *pAuxObject;
} Ov000BootContext;

extern Ov000BootContext *NNSi_FndGetCurrentRootHeap(void);
extern void KeyRepeat_Step(void *image);
extern u16 Mem_ReadU16(const void *image);
extern void Ov000_SetPendingMenuId(u16 id);
extern void Camera_CommitMatricesEx(void *bounds, int left, int right,
                          int top, int bottom);
extern void Scene_DrawNode(void *renderNode);
extern int Ov000_GetLoadState(void);
extern int Ov000_GetLoadResultA(void);
extern int Ov000_GetLoadResultB(void);
extern void *VeneerTo_Obj_Destroy(void *handle);
extern void Ov000_PreloadLogoResources(void);
extern void Ov000_Title_CreateLogoObjects(void);
extern void Ov000_ReleaseLogoResources(void);
extern void StampByteAndInvokeSubStructAt(int first, int second);
extern void Table_TailCallWithEntry(int first, int second);
extern void Ov000_ReentryState(void);
extern void Ov000_TickBootFadeTransition(void);

Ov000StateFn Ov000_TickBootTeardown(void) {
    Ov000BootContext *context = NNSi_FndGetCurrentRootHeap();
    int state;

    KeyRepeat_Step(context->overlayImage);
    Ov000_SetPendingMenuId(Mem_ReadU16(context->overlayImage));
    Camera_CommitMatricesEx(context->scrollBounds, 0x3b33, -0x3b33,
                  -0x4d9a, 0x4d9a);
    Scene_DrawNode(context->renderNode);

    state = Ov000_GetLoadState();
    switch (state) {
    case 7:
        context->savedSceneFlag = Ov000_GetLoadResultA();
        context->savedSceneId = Ov000_GetLoadResultB();
        VeneerTo_Obj_Destroy(context->pSceneObject);
        context->pSceneObject = context->pAuxObject = 0;
        *(volatile u32 *)0x04001000 &= ~0xe000;

        Ov000_PreloadLogoResources();
        Ov000_Title_CreateLogoObjects();
        Ov000_ReleaseLogoResources();
        if (context->savedSceneFlag == 0) {
            context->resumeBoot = 0;
        }
        return Ov000_ReentryState;
    case 8:
        context->frame = 0;
        context->transitionFlag = 1;
        StampByteAndInvokeSubStructAt(1, 3);
        Table_TailCallWithEntry(0, 0x1e);
        return Ov000_TickBootFadeTransition;
    default:
        return 0;
    }
}
