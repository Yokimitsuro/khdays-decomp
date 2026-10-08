/* Ov026_FillSceneHooks -- Ov025_FillSceneHooks: fill the ov002 root's sub-flow hook table
 * (root +0x8b7c, handed over by ov002 0206a4d4 once this overlay is loaded) with the records
 * scene's handlers: the display setup (02082a48), the callback registration and removal
 * (02082b1c / 02082b40), the state-bit setters and tests on the shared state word
 * (02082b84, 02082ba4, 02082bc0, 02082b64), no event hook, and the stub 02082bd8 at +0x24.
 * Twin of ov027 02083dbc / ov026 02082b4c. */
typedef struct Ov002SceneHooks {
    void (*pfnSetup)(void);          /* 0x00 */
    void (*pfnCreateTask)(int nArg); /* 0x04 */
    void (*pfnDestroyTask)(void);    /* 0x08 */
    void (*pfnActivate)(void);       /* 0x0c */
    void (*pfnDeactivate)(void);     /* 0x10 */
    int  (*pfnIsActive)(void);       /* 0x14 */
    int  (*pfnIsIdle)(void);         /* 0x18 */
    void (*pfnOnEvent)(int nEvent);  /* 0x1c */
    void (*pfnField20)(void);        /* 0x20 */
    int  (*pfnField24)(void);        /* 0x24 */
    void (*pfnField28)(void);        /* 0x28 */
} Ov002SceneHooks;

extern void  Ov026_BlankScreens(void);                             /* Ov025_SetupDisplay */
extern void  Ov026_CreateService(int nArg);                         /* Ov025_RegisterCallback */
extern void  Ov026_DestroyService(void);                             /* Ov025_UnregisterCallback */
extern void  Ov026_SceneActivate(void);                             /* Ov025_SetStateActive */
extern void  Ov026_SetMenuFlag4(void);                             /* Ov025_SetStateDone */
extern int   Ov026_SceneIsActive(void);                             /* Ov025_IsStateDone */
extern int   Ov026_SceneIsIdle(void);                             /* Ov025_IsStateIdle */
extern int   Ov026_SceneHook24NoOp(void);                             /* returns 0 */

void Ov026_FillSceneHooks(Ov002SceneHooks *pHooks)
{
    pHooks->pfnSetup = Ov026_BlankScreens;
    pHooks->pfnCreateTask = Ov026_CreateService;
    pHooks->pfnDestroyTask = Ov026_DestroyService;
    pHooks->pfnActivate = Ov026_SceneActivate;
    pHooks->pfnDeactivate = Ov026_SetMenuFlag4;
    pHooks->pfnIsActive = Ov026_SceneIsActive;
    pHooks->pfnIsIdle = Ov026_SceneIsIdle;
    pHooks->pfnOnEvent = 0;
    pHooks->pfnField24 = Ov026_SceneHook24NoOp;
    pHooks->pfnField28 = 0;
}
