/* ov008 page hooks data_ov008_020907a0, 0x020907a0-0x020907e0 (.data): the menu state page (Ov008_TickMenuState, 0x240-byte state).
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

extern void func_ov008_0206e878(void);
extern void func_ov008_0206e984(void);
extern void func_ov008_0206ea38(void);
extern void func_ov008_0206ea84(void);

Ov008PageHooks data_ov008_020907a0 = {
    func_ov008_0206e878,  /* pfnOpen */
    func_ov008_0206e984,  /* pfnStep */
    func_ov008_0206ea38,  /* pfnClose */
    576,  /* nStateSize */
    { 0, 0, 0, 0, 0, 0, func_ov008_0206ea84, 0, 0, 0, 0, 0 },  /* apfnHook */
};
