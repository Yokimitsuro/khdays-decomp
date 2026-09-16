/* ov008 screen hooks data_ov008_02090460, 0x02090460-0x020904a4 (.data): the grid screen (02068904 .. 02068ba8, 0x1f00-byte state).
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

extern void func_ov008_02068588(void);
extern void func_ov008_020685d0(void);
extern void func_ov008_0206861c(void);
extern void func_ov008_020686a0(void);
extern void func_ov008_02068728(void);
extern void func_ov008_02068878(void);
extern void func_ov008_02068904(void);
extern void func_ov008_02068b10(void);
extern void func_ov008_02068ba8(void);

Ov008ScreenHooks data_ov008_02090460 = {
    func_ov008_02068904,  /* pfnOpen */
    func_ov008_02068b10,  /* pfnStep */
    func_ov008_02068ba8,  /* pfnClose */
    0,  /* nFlags */
    7936,  /* nStateSize */
    func_ov008_02068588,  /* pfnSelect */
    func_ov008_020685d0,  /* pfnCancel */
    { func_ov008_020686a0, func_ov008_0206861c },  /* apfnAux */
    func_ov008_02068728,  /* pfnDone */
    { func_ov008_02068878, 0, 0, 0, 0, 0, func_ov008_02068878 },  /* apfnHook */
};
