/* Boot fade-in tick: darken-to-lit over 16 frames, then hand off to the menu loop.
 *
 * SetMasterBrightnessSub/0201e374 are SetMasterBrightnessSub/Main; the argument runs step-16 (i.e. -16..0),
 * so this is a master-brightness fade from black up to full. Sub is always driven; Main only when
 * the scene object (pResource5074) is non-null. On the frame the counter passes 16 it pins the
 * counter to 120, stamps GetTick64 into llTimestamp, and returns Ov000_TickMenuLoop as the next
 * scene tick. Same 0xd18c Ov000SceneContext as the other menu ticks; +0 is read as a 32-bit frame
 * counter here (the reading the type's +0 comment records).
 */

#include "nitro/types.h"
#include "game/engine.h"

typedef void (*OverlayCallback)(void);

typedef struct {
    int nStateFrame;         /* +0x00 */
    u8 pad_0004[8];
    u8 renderNode[0x108];    /* +0x0c */
    u8 scrollBounds[0x4b50]; /* +0x114 */
    u64 llTimestamp;         /* +0x4c64 */
    u8 pad_4c6c[0x408];
    void *pResource5074;     /* +0x5074 -- shared-resource handle, gates the Main fade */
} Ov000SceneContext;

extern Ov000SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void Camera_CommitMatricesEx(void *bounds, int right, int left, int top,
                           int bottom);
extern void Scene_DrawNode(void *object);
extern u64 OS_GetTick(void);
extern void Ov000_TickMenuLoop(void);

OverlayCallback Ov000_TickBootFadeIn(void) {
    Ov000SceneContext *context = NNSi_FndGetCurrentRootHeap();

    Camera_CommitMatricesEx(context->scrollBounds, 0x3b33, -0x3b33, -0x4d9a,
                  0x4d9a);
    Scene_DrawNode(context->renderNode);

    if (context->nStateFrame <= 16) {
        SetMasterBrightnessSub(context->nStateFrame - 16);
        if (context->pResource5074 != 0) {
            SetMasterBrightnessMain(context->nStateFrame - 16);
        }
    } else {
        SetMasterBrightnessSub(0);
        if (context->pResource5074 != 0) {
            SetMasterBrightnessMain(context->nStateFrame - 16);
        }
        context->nStateFrame = 120;
        context->llTimestamp = OS_GetTick();
        return Ov000_TickMenuLoop;
    }

    context->nStateFrame++;
    return 0;
}
