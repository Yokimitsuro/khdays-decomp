/* Ov023_InstallSceneInterface -- Ov023_InstallSceneInterface: fill the caller's handler table with the
 * event scene's entry points -- display setup (Ov023_SetupDisplay 02082a80), create the scene's
 * task (02082bdc), destroy it (02082c00), close the prompt (02082c24), mark done / is done
 * (02082c80 / 02082c9c, status bit 4) --
 * and clear the state words the handlers own (+0x18, +0x1c, +0x24, +0x28).  The mirror of the
 * MobiClip player's table (ov024 020832c4) for the event scene. */
typedef struct Ov023SceneInterface {
    void (*pfnSetupDisplay)(void);          /* 0x00 */
    void (*pfnCreateTask)(int nArg);        /* 0x04 */
    void (*pfnDestroyTask)(void);           /* 0x08 */
    void (*pfnClosePrompt)(void);           /* 0x0c */
    void (*pfnMarkDone)(void);              /* 0x10: raise status bit 4 */
    void (*pfnIsDone)(void);                /* 0x14: status bit 4 set? */
    int  nState18;                          /* 0x18 */
    int  nState1c;                          /* 0x1c */
    int  nField20;                          /* 0x20 */
    int  nState24;                          /* 0x24 */
    int  nState28;                          /* 0x28 */
} Ov023SceneInterface;

extern void Ov023_SetupDisplay(void);
extern void Ov023_CreateSceneTask(int nArg);
extern void Ov023_DestroySceneTask(void);
extern void Ov023_ClosePrompt(void);
extern void Ov023_SceneMarkDone(void);
extern void Ov023_SceneIsDone(void);

void Ov023_InstallSceneInterface(Ov023SceneInterface *pTable)
{
    pTable->pfnSetupDisplay = Ov023_SetupDisplay;
    pTable->pfnCreateTask = Ov023_CreateSceneTask;
    pTable->pfnDestroyTask = Ov023_DestroySceneTask;
    pTable->pfnClosePrompt = Ov023_ClosePrompt;
    pTable->pfnMarkDone = Ov023_SceneMarkDone;
    pTable->pfnIsDone = Ov023_SceneIsDone;
    pTable->nState18 = 0;
    pTable->nState1c = 0;
    pTable->nState24 = 0;
    pTable->nState28 = 0;
}
