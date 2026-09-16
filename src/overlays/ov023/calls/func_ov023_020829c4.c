/* func_ov023_020829c4 -- Ov023_SceneLeave: exit of the event scene.  Ends the key-sharing
 * session of the scene's main object (context +4, 02023ad0), then loads the protected overlay
 * ov028 and runs its predicates with the global-swap routine Ov023_SwapSharedWords (02082c5c)
 * as their argument: unless 0208b040 objects, a positive 0208b490 verdict drops the open source
 * handle (data_ov023_0208a000 = -1) and the context pointer (data_ov023_0208a780 = 0) before
 * 0208b200 runs; ov028 is unloaded again.  The overlay id is the linker-absolute
 * OVERLAY_28_ID, loaded from the pool and CSE'd into r4 across both calls. */
typedef unsigned int u32;
typedef u32 FSOverlayID;

typedef struct Ov023SceneContext {
    u32  nStatus;             /* 0x00 */
    void *pMain;              /* 0x04 */
} Ov023SceneContext;

/* FS_EXTERN_OVERLAY(ov028) -- dsd names the absolute symbol OVERLAY_28_ID. */
extern u32 OVERLAY_28_ID[1];
#define FS_OVERLAY_ID_ov028 ((FSOverlayID)(u32) & (OVERLAY_28_ID))

extern Ov023SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void  WM_EndKeySharing_0x02023ad0(void *pObject);           /* end the key-sharing session */
extern void  func_0201e470(int nProcessor, FSOverlayID nOverlay);   /* FS_LoadOverlay */
extern void  func_0201e4a8(int nProcessor, FSOverlayID nOverlay);   /* FS_UnloadOverlay */
extern int   func_ov028_0208b040(void (*pfn)(void));                /* anti-tamper predicates in ov028's encrypted block */
extern int   func_ov028_0208b490(int nArg);
extern int   func_ov028_0208b200(void (*pfn)(void));
extern void  func_ov023_02082c5c(void);                             /* Ov023_SwapSharedWords */
extern int   data_ov023_0208a000;                                   /* the open source handle */
extern Ov023SceneContext *data_ov023_0208a780;

void func_ov023_020829c4(void)
{
    WM_EndKeySharing_0x02023ad0(NNSi_FndGetCurrentRootHeap()->pMain);
    func_0201e470(0, FS_OVERLAY_ID_ov028);
    if (func_ov028_0208b040(func_ov023_02082c5c) == 0) {
        if (func_ov028_0208b490(0) != 0) {
            data_ov023_0208a000 = -1;
            data_ov023_0208a780 = 0;
        }
        func_ov028_0208b200(func_ov023_02082c5c);
    }
    func_0201e4a8(0, FS_OVERLAY_ID_ov028);
}
