/* ov025 screen hooks data_ov025_020b4b70, 0x020b4b70-0x020b4bb4 (.data): the records hub screen (Ov025_SetupScene 0208be04 / teardown 0208beb4 / step 0208bf58, 0x5cc-byte Ov025HubScene; back 0208bda0, veneer 0208bdf8 in the last slot).
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

extern void WM_EndKeySharing_0x0208bdf8(void);
extern void func_ov025_0208bda0(void);
extern void func_ov025_0208be04(void);
extern void func_ov025_0208beb4(void);
extern void func_ov025_0208bf58(void);

Ov008ScreenHooks data_ov025_020b4b70 = {
    func_ov025_0208be04,  /* pfnOpen */
    func_ov025_0208beb4,  /* pfnStep */
    func_ov025_0208bf58,  /* pfnClose */
    0,  /* nFlags */
    1484,  /* nStateSize */
    0,  /* pfnSelect */
    0,  /* pfnCancel */
    { 0, 0 },  /* apfnAux */
    0,  /* pfnDone */
    { func_ov025_0208bda0, 0, 0, 0, 0, 0, WM_EndKeySharing_0x0208bdf8 },  /* apfnHook */
};
