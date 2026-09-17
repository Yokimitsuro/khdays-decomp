/* ov025 screen hooks data_ov025_020b4cb4, 0x020b4cb4-0x020b4cf8 (.data): the main menu screen (Ov008_MainMenu_StateTick 0208d730 / teardown 0208d904 / timer 0208d9a4, flags 1, 0x1500-byte state).
 */

typedef void (*Ov008HookFn)(void);

/* 0x44-byte screen class: entered / stepped / left through the first three
 * slots by index (the ov008 screen dispatcher 020513bc / 020513f0 family via the
 * slot table data_ov025_020b4ab0); the list menus read pfnSelect / pfnCancel /
 * pfnDone (data_ov025_020b4d4c is rebound by 02099558 / 020995cc). */
typedef struct Ov008ScreenHooks {
    Ov008HookFn pfnOpen;      /* 0x00 */
    Ov008HookFn pfnStep;      /* 0x04 */
    Ov008HookFn pfnClose;     /* 0x08 */
    int nFlags;               /* 0x0c */
    int nStateSize;           /* 0x10 */
    Ov008HookFn pfnSelect;    /* 0x14 */
    Ov008HookFn pfnCancel;    /* 0x18 */
    Ov008HookFn apfnAux[2];   /* 0x1c */
    Ov008HookFn pfnDone;      /* 0x24 */
    Ov008HookFn apfnHook[7];  /* 0x28 .. 0x40 */
} Ov008ScreenHooks;

extern void func_ov025_0208d730(void);
extern void func_ov025_0208d904(void);
extern void func_ov025_0208d9a4(void);

Ov008ScreenHooks data_ov025_020b4cb4 = {
    func_ov025_0208d730,  /* pfnOpen */
    func_ov025_0208d904,  /* pfnStep */
    func_ov025_0208d9a4,  /* pfnClose */
    1,  /* nFlags */
    5376,  /* nStateSize */
    0,  /* pfnSelect */
    0,  /* pfnCancel */
    { 0, 0 },  /* apfnAux */
    0,  /* pfnDone */
    { 0, 0, 0, 0, 0, 0, 0 },  /* apfnHook */
};
