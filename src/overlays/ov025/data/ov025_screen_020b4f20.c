/* ov025 screen hooks data_ov025_020b4f20, 0x020b4f20-0x020b4f64 (.data): the config screen (0209d564 / 0209d590 / 0209d610, 188-byte state).
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

extern void func_ov025_0209d564(void);
extern void func_ov025_0209d590(void);
extern void func_ov025_0209d610(void);

Ov008ScreenHooks data_ov025_020b4f20 = {
    func_ov025_0209d564,  /* pfnOpen */
    func_ov025_0209d590,  /* pfnStep */
    func_ov025_0209d610,  /* pfnClose */
    0,  /* nFlags */
    188,  /* nStateSize */
    0,  /* pfnSelect */
    0,  /* pfnCancel */
    { 0, 0 },  /* apfnAux */
    0,  /* pfnDone */
    { 0, 0, 0, 0, 0, 0, 0 },  /* apfnHook */
};
