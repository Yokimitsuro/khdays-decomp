/* Ov023_SceneLeave -- Ov023_SceneLeave: exit of the event scene.  Destroys the
 * scene's main object (the root heap's +4, Obj_Destroy through its veneer), then loads the protected overlay
 * ov028 and runs its predicates with the global-swap routine Ov023_SwapSharedWords (02082c5c)
 * as their argument: unless DSProt_DetectFlashcart objects, a positive DSProt_DetectNotDummy
 * verdict forgets the scene task's handle (data_ov023_0208a000 = -1) and the context pointer
 * (data_ov023_0208a780 = 0) before DSProt_DetectEmulator runs; ov028 is unloaded again.  The overlay id is the linker-absolute
 * OVERLAY_28_ID, loaded from the pool and CSE'd into r4 across both calls. */

#include "nitro/types.h"
#include "game/engine.h"

typedef u32 FSOverlayID;

typedef struct Ov023SceneContext {
    u32  nStatus;             /* 0x00 */
    void *pMain;              /* 0x04 */
} Ov023SceneContext;

/* FS_EXTERN_OVERLAY(ov028) -- dsd names the absolute symbol OVERLAY_28_ID. */
extern u32 OVERLAY_28_ID[1];
#define FS_OVERLAY_ID_ov028 ((FSOverlayID)(u32) & (OVERLAY_28_ID))

extern Ov023SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void  VeneerTo_Obj_Destroy(void *pObject);           /* Obj_Destroy */
extern int   Ov028_DSProt_DetectFlashcart(void (*pfn)(void));                /* anti-tamper predicates in ov028's encrypted block */
extern int   Ov028_DSProt_DetectNotDummy(int nArg);
extern int   Ov028_DSProt_DetectEmulator(void (*pfn)(void));
extern void  Ov023_SwapGlobalPair(void);                             /* Ov023_SwapSharedWords */
extern int   data_ov023_0208a000;                                   /* the open source handle */
extern Ov023SceneContext *data_ov023_0208a780;

void Ov023_SceneLeave(void)
{
    VeneerTo_Obj_Destroy(NNSi_FndGetCurrentRootHeap()->pMain);
    LoadOverlaySync(0, FS_OVERLAY_ID_ov028);
    if (Ov028_DSProt_DetectFlashcart(Ov023_SwapGlobalPair) == 0) {
        if (Ov028_DSProt_DetectNotDummy(0) != 0) {
            data_ov023_0208a000 = -1;
            data_ov023_0208a780 = 0;
        }
        Ov028_DSProt_DetectEmulator(Ov023_SwapGlobalPair);
    }
    UnloadOverlaySync(0, FS_OVERLAY_ID_ov028);
}
