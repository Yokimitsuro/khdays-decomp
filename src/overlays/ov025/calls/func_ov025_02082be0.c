/* func_ov025_02082be0 -- Ov025_FillSceneHooks: fill the ov002 root's sub-flow hook table
 * (root +0x8b7c, handed over by ov002 0206a4d4 once this overlay is loaded) with the records
 * scene's handlers: the display setup (02082a48), the callback registration and removal
 * (02082b1c / 02082b40), the state-bit setters and tests on the shared state word
 * (02082b84, 02082ba4, 02082bc0, 02082b64), no event hook, and the stub 02082bd8 at +0x24.
 * Twin of ov027 02083dbc / ov026 02082b4c. */
typedef struct Ov002SceneHooks {
    void (*pfnSetup)(void);          /* 0x00 */
    void (*pfnRegister)(int nArg);   /* 0x04 */
    void (*pfnUnregister)(void);     /* 0x08 */
    void (*pfnActivate)(void);       /* 0x0c */
    void (*pfnDeactivate)(void);     /* 0x10 */
    int  (*pfnIsActive)(void);       /* 0x14 */
    int  (*pfnIsIdle)(void);         /* 0x18 */
    void (*pfnOnEvent)(int nEvent);  /* 0x1c */
    void (*pfnField20)(void);        /* 0x20 */
    int  (*pfnField24)(void);        /* 0x24 */
    void (*pfnField28)(void);        /* 0x28 */
} Ov002SceneHooks;

extern void  func_ov025_02082a48(void);                             /* Ov025_SetupDisplay */
extern void  func_ov025_02082b1c(int nArg);                         /* Ov025_RegisterCallback */
extern void  func_ov025_02082b40(void);                             /* Ov025_UnregisterCallback */
extern void  func_ov025_02082b84(void);                             /* Ov025_SetStateActive */
extern void  func_ov025_02082ba4(void);                             /* Ov025_SetStateDone */
extern int   func_ov025_02082bc0(void);                             /* Ov025_IsStateDone */
extern int   func_ov025_02082b64(void);                             /* Ov025_IsStateIdle */
extern int   func_ov025_02082bd8(void);                             /* returns 0 */

void func_ov025_02082be0(Ov002SceneHooks *pHooks)
{
    pHooks->pfnSetup = func_ov025_02082a48;
    pHooks->pfnRegister = func_ov025_02082b1c;
    pHooks->pfnUnregister = func_ov025_02082b40;
    pHooks->pfnActivate = func_ov025_02082b84;
    pHooks->pfnDeactivate = func_ov025_02082ba4;
    pHooks->pfnIsActive = func_ov025_02082bc0;
    pHooks->pfnIsIdle = func_ov025_02082b64;
    pHooks->pfnOnEvent = 0;
    pHooks->pfnField24 = func_ov025_02082bd8;
    pHooks->pfnField28 = 0;
}
