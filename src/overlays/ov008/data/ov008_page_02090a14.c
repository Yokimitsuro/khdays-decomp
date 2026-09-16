/* ov008 page hooks data_ov008_02090a14, 0x02090a14-0x02090a54 (.data): the mission detail page (02078df0 .. 020791e0, 0x214-byte state).
 */

typedef void (*Ov008HookFn)(void);

/* 0x40-byte page class: entered / stepped / left through the first three
 * slots by index (Ov008_Fn_1458 and its +4 / +8 siblings), then the state
 * size and twelve page hooks. */
typedef struct Ov008PageHooks {
    Ov008HookFn pfnOpen;      /* 0x00 */
    Ov008HookFn pfnStep;      /* 0x04 */
    Ov008HookFn pfnClose;     /* 0x08 */
    int nStateSize;           /* 0x0c */
    Ov008HookFn apfnHook[12]; /* 0x10 .. 0x3c */
} Ov008PageHooks;

extern void func_ov008_02078df0(void);
extern void func_ov008_02078e68(void);
extern void func_ov008_02079038(void);
extern void func_ov008_02079090(void);
extern void func_ov008_02079118(void);
extern void func_ov008_020791e0(void);

Ov008PageHooks data_ov008_02090a14 = {
    func_ov008_02078df0,  /* pfnOpen */
    func_ov008_02078e68,  /* pfnStep */
    func_ov008_02079038,  /* pfnClose */
    532,  /* nStateSize */
    { 0, 0, 0, 0, 0, 0, 0, 0, func_ov008_02079090, func_ov008_02079118, 0, func_ov008_020791e0 },  /* apfnHook */
};
