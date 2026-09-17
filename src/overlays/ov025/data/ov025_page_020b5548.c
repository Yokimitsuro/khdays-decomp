/* ov025 page hooks data_ov025_020b5548, 0x020b5548-0x020b5588 (.data): the mission detail page (Ov025_SetupShopScreen 020af848 / 020af8c0 / 020afa90, 0x214-byte state).
 */

typedef void (*Ov008HookFn)(void);

/* 0x40-byte page class: entered / stepped / left through the first three
 * slots by index (the ov008 page dispatcher 02051498 / 020514cc family via the
 * slot table data_ov025_020b4a78), then the state size and twelve page hooks. */
typedef struct Ov008PageHooks {
    Ov008HookFn pfnOpen;      /* 0x00 */
    Ov008HookFn pfnStep;      /* 0x04 */
    Ov008HookFn pfnClose;     /* 0x08 */
    int nStateSize;           /* 0x0c */
    Ov008HookFn apfnHook[12]; /* 0x10 .. 0x3c */
} Ov008PageHooks;

extern void func_ov025_020af848(void);
extern void func_ov025_020af8c0(void);
extern void func_ov025_020afa90(void);
extern void func_ov025_020afae8(void);
extern void func_ov025_020afb70(void);
extern void func_ov025_020afc38(void);

Ov008PageHooks data_ov025_020b5548 = {
    func_ov025_020af848,  /* pfnOpen */
    func_ov025_020af8c0,  /* pfnStep */
    func_ov025_020afa90,  /* pfnClose */
    532,  /* nStateSize */
    { 0, 0, 0, 0, 0, 0, 0, 0, func_ov025_020afae8, func_ov025_020afb70, 0, func_ov025_020afc38 },  /* apfnHook */
};
