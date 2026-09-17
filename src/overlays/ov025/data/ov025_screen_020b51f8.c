/* ov025 screen hooks data_ov025_020b51f8, 0x020b51f8-0x020b523c (.data): the reports page (020a086c / Ov025_Reports_Teardown 020a08c0 / Ov025_Reports_HandleInput 020a0a9c, flags 6, 0x278-byte Ov025ReportsPage; cursor 0209fa88 / 0209fc64, pages 0209fe48 / 0209ffd0).
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

extern void func_ov025_0209fa88(void);
extern void func_ov025_0209fc64(void);
extern void func_ov025_0209fe48(void);
extern void func_ov025_0209ffd0(void);
extern void func_ov025_020a018c(void);
extern void func_ov025_020a01bc(void);
extern void func_ov025_020a086c(void);
extern void func_ov025_020a08c0(void);
extern void func_ov025_020a0a9c(void);

Ov008ScreenHooks data_ov025_020b51f8 = {
    func_ov025_020a086c,  /* pfnOpen */
    func_ov025_020a08c0,  /* pfnStep */
    func_ov025_020a0a9c,  /* pfnClose */
    6,  /* nFlags */
    632,  /* nStateSize */
    func_ov025_0209fa88,  /* pfnSelect */
    func_ov025_0209fc64,  /* pfnCancel */
    { func_ov025_0209fe48, func_ov025_0209ffd0 },  /* apfnAux */
    0,  /* pfnDone */
    { func_ov025_020a018c, 0, 0, func_ov025_020a01bc, func_ov025_020a01bc, 0, func_ov025_020a018c },  /* apfnHook */
};
