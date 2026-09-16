/* func_ov023_02082960 -- Ov023_SceneEnter: entry state of the event scene (ov023).  Takes the
 * current scene context (NNSi_FndGetCurrentRootHeap, kept in data_ov023_0208a780), touches
 * the slot table (020315f4), sets the status halfword to 1, builds the class arguments -- a
 * copy of the request (func_0201f924) followed by the request's byte at +0x7f -- and creates
 * the scene's main object (func_02023930 on the class descriptor data_ov023_0208a038), kept at
 * context +4.  Moves on to the first-frame gate Ov023_SceneFirstFrame (02082a44). */
typedef unsigned short u16;

typedef struct Ov023SceneContext {
    u16  nStatus;             /* 0x00 */
    u16  pad_02;
    void *pMain;              /* 0x04 */
} Ov023SceneContext;

typedef struct Ov023SceneRequest {
    char szName[0x7f];        /* 0x00 */
    char nKind;               /* 0x7f */
} Ov023SceneRequest;

typedef struct Ov023MainArgs {
    char request[0x44];       /* 0x00 */
    int  nKind;               /* 0x44 */
} Ov023MainArgs;

extern Ov023SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern void  CARDi_GetRomAccessor_0x020315f4(void);                /* Session_GetSlotTable */
extern void  func_0201f924(void *pDst, const void *pSrc);            /* copy a request record */
extern void *func_02023930(void *pClass, void *pArgs);               /* InstantiateClass */
extern int   func_ov023_02082a44(void);                              /* Ov023_SceneFirstFrame */
extern Ov023SceneContext *data_ov023_0208a780;
extern char  data_ov023_0208a038[];                                  /* the main object's class */

void *func_ov023_02082960(Ov023SceneRequest *pRequest)
{
    Ov023MainArgs args;
    Ov023SceneContext *pContext;

    pContext = NNSi_FndGetCurrentRootHeap();
    CARDi_GetRomAccessor_0x020315f4();
    data_ov023_0208a780 = pContext;
    pContext->nStatus = 1;
    func_0201f924(&args, pRequest);
    args.nKind = pRequest->nKind;
    pContext->pMain = func_02023930(data_ov023_0208a038, &args);
    return func_ov023_02082a44;
}
