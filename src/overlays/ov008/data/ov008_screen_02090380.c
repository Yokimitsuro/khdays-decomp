/* ov008 screen hooks data_ov008_02090380, 0x02090380-0x020903c4 (.data): the list menu screen (020659c0 .. 02066b10, 0x20a0-byte state).
 */

typedef void (*Ov008HookFn)(void);

/* 0x44-byte screen class: entered / stepped / left through the first three
 * slots by index (Ov008_Fn_137c and its +4 / +8 siblings); the list menus
 * read pfnSelect / pfnCancel / pfnDone (Ov008_FinishMenuModeSwitch). */
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

extern void func_ov008_020659c0(void);
extern void func_ov008_02065ce8(void);
extern void func_ov008_02065e94(void);
extern void func_ov008_02065f80(void);
extern void func_ov008_0206608c(void);
extern void func_ov008_02066194(void);
extern void func_ov008_02066294(void);
extern void func_ov008_02066394(void);
extern void func_ov008_020665a8(void);
extern void func_ov008_02066974(void);
extern void func_ov008_020669e0(void);
extern void func_ov008_02066a4c(void);
extern void func_ov008_02066ac8(void);
extern void func_ov008_02066b10(void);

Ov008ScreenHooks data_ov008_02090380 = {
    func_ov008_020659c0,  /* pfnOpen */
    func_ov008_02065ce8,  /* pfnStep */
    func_ov008_02065e94,  /* pfnClose */
    0,  /* nFlags */
    8352,  /* nStateSize */
    func_ov008_02065f80,  /* pfnSelect */
    func_ov008_0206608c,  /* pfnCancel */
    { func_ov008_02066194, func_ov008_02066294 },  /* apfnAux */
    func_ov008_02066394,  /* pfnDone */
    { func_ov008_020665a8, 0, func_ov008_02066a4c, func_ov008_02066974, func_ov008_020669e0, func_ov008_02066ac8, func_ov008_02066b10 },  /* apfnHook */
};
