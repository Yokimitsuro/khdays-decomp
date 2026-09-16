/* func_ov023_02082cc0 -- Ov023_InstallSceneInterface: fill the caller's handler table with the
 * event scene's entry points -- display setup (Ov023_SetupDisplay 02082a80), open a source
 * (02082bdc), end key sharing (02082c00), close the prompt (02082c24), mark done / is done
 * (02082c80 / 02082c9c, status bit 4) --
 * and clear the state words the handlers own (+0x18, +0x1c, +0x24, +0x28).  The mirror of the
 * MobiClip player's table (ov024 020832c4) for the event scene. */
typedef struct Ov023SceneInterface {
    void (*pfnSetupDisplay)(void);          /* 0x00 */
    void (*pfnOpen)(int nArg);              /* 0x04 */
    void (*pfnEndKeySharing)(void);         /* 0x08 */
    void (*pfnClosePrompt)(void);           /* 0x0c */
    void (*pfnMarkDone)(void);              /* 0x10: raise status bit 4 */
    void (*pfnIsDone)(void);                /* 0x14: status bit 4 set? */
    int  nState18;                          /* 0x18 */
    int  nState1c;                          /* 0x1c */
    int  nField20;                          /* 0x20 */
    int  nState24;                          /* 0x24 */
    int  nState28;                          /* 0x28 */
} Ov023SceneInterface;

extern void func_ov023_02082a80(void);
extern void func_ov023_02082bdc(int nArg);
extern void func_ov023_02082c00(void);
extern void func_ov023_02082c24(void);
extern void func_ov023_02082c80(void);
extern void func_ov023_02082c9c(void);

void func_ov023_02082cc0(Ov023SceneInterface *pTable)
{
    pTable->pfnSetupDisplay = func_ov023_02082a80;
    pTable->pfnOpen = func_ov023_02082bdc;
    pTable->pfnEndKeySharing = func_ov023_02082c00;
    pTable->pfnClosePrompt = func_ov023_02082c24;
    pTable->pfnMarkDone = func_ov023_02082c80;
    pTable->pfnIsDone = func_ov023_02082c9c;
    pTable->nState18 = 0;
    pTable->nState1c = 0;
    pTable->nState24 = 0;
    pTable->nState28 = 0;
}
