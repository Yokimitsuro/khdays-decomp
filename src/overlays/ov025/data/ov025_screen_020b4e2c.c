/* ov025 screen hooks data_ov025_020b4e2c, 0x020b4e2c-0x020b4e70 (.data): the grid screen (0209ace4 .. 0209af88, 0x1f00-byte state).
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

extern void func_ov025_0209a968(void);
extern void func_ov025_0209a9b0(void);
extern void func_ov025_0209a9fc(void);
extern void func_ov025_0209aa80(void);
extern void func_ov025_0209ab08(void);
extern void func_ov025_0209ac58(void);
extern void func_ov025_0209ace4(void);
extern void func_ov025_0209aef0(void);
extern void func_ov025_0209af88(void);

Ov008ScreenHooks data_ov025_020b4e2c = {
    func_ov025_0209ace4,  /* pfnOpen */
    func_ov025_0209aef0,  /* pfnStep */
    func_ov025_0209af88,  /* pfnClose */
    0,  /* nFlags */
    7936,  /* nStateSize */
    func_ov025_0209a968,  /* pfnSelect */
    func_ov025_0209a9b0,  /* pfnCancel */
    { func_ov025_0209aa80, func_ov025_0209a9fc },  /* apfnAux */
    func_ov025_0209ab08,  /* pfnDone */
    { func_ov025_0209ac58, 0, 0, 0, 0, 0, func_ov025_0209ac58 },  /* apfnHook */
};
