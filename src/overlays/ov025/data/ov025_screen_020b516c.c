/* ov025 screen hooks data_ov025_020b516c, 0x020b516c-0x020b51b0 (.data): the tutorial page (Ov025_Tutorial_Setup 0209e41c / teardown 0209e490 / input 0209e5e8, flags 4, 0x2b0-byte Ov025TutorialPage; cursor 0209de5c / 0209df14, pages 0209dfbc / 0209e060).
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

extern void func_ov025_0209de5c(void);
extern void func_ov025_0209df14(void);
extern void func_ov025_0209dfbc(void);
extern void func_ov025_0209e060(void);
extern void func_ov025_0209e128(void);
extern void func_ov025_0209e168(void);
extern void func_ov025_0209e194(void);
extern void func_ov025_0209e41c(void);
extern void func_ov025_0209e490(void);
extern void func_ov025_0209e5e8(void);

Ov008ScreenHooks data_ov025_020b516c = {
    func_ov025_0209e41c,  /* pfnOpen */
    func_ov025_0209e490,  /* pfnStep */
    func_ov025_0209e5e8,  /* pfnClose */
    4,  /* nFlags */
    688,  /* nStateSize */
    func_ov025_0209de5c,  /* pfnSelect */
    func_ov025_0209df14,  /* pfnCancel */
    { func_ov025_0209dfbc, func_ov025_0209e060 },  /* apfnAux */
    func_ov025_0209e194,  /* pfnDone */
    { func_ov025_0209e128, 0, 0, func_ov025_0209e168, func_ov025_0209e194, 0, func_ov025_0209e128 },  /* apfnHook */
};
