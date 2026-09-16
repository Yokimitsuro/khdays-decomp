/* ov008 page hooks data_ov008_020908e0, 0x020908e0-0x02090920 (.data): the mission menu page (02077b28 .. 02078154, 0x570-byte state).
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

extern void WM_EndKeySharing_0x02078154(void);
extern void func_ov008_02077b28(void);
extern void func_ov008_02077d64(void);
extern void func_ov008_02077eb4(void);
extern void func_ov008_02077ee4(void);
extern void func_ov008_02077f00(void);
extern void func_ov008_02077f1c(void);
extern void func_ov008_02077f8c(void);
extern void func_ov008_02077ffc(void);
extern void func_ov008_02078088(void);
extern void func_ov008_020780cc(void);
extern void func_ov008_02078110(void);

Ov008PageHooks data_ov008_020908e0 = {
    func_ov008_02077b28,  /* pfnOpen */
    func_ov008_02077d64,  /* pfnStep */
    func_ov008_02077eb4,  /* pfnClose */
    1392,  /* nStateSize */
    { func_ov008_02077ee4, func_ov008_02077f00, func_ov008_02077f1c, func_ov008_02077f8c, func_ov008_02077ffc, func_ov008_02078088, 0, 0, func_ov008_020780cc, func_ov008_02078110, 0, WM_EndKeySharing_0x02078154 },  /* apfnHook */
};
