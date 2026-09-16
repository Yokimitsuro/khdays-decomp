/* ov008 page hooks data_ov008_0209082c, 0x0209082c-0x0209086c (.data): the mission list page (Ov008_MissionListInitStep .. 02073df0, 0x508-byte state).
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

extern void func_ov008_02073564(void);
extern void func_ov008_0207378c(void);
extern void func_ov008_02073994(void);
extern void func_ov008_02073a04(void);
extern void func_ov008_02073acc(void);
extern void func_ov008_02073b78(void);
extern void func_ov008_02073be0(void);
extern void func_ov008_02073c48(void);
extern void func_ov008_02073cec(void);
extern void func_ov008_02073d88(void);
extern void func_ov008_02073df0(void);

Ov008PageHooks data_ov008_0209082c = {
    func_ov008_02073564,  /* pfnOpen */
    func_ov008_0207378c,  /* pfnStep */
    func_ov008_02073994,  /* pfnClose */
    1288,  /* nStateSize */
    { func_ov008_02073a04, func_ov008_02073acc, func_ov008_02073b78, func_ov008_02073be0, func_ov008_02073c48, func_ov008_02073cec, 0, 0, func_ov008_02073d88, func_ov008_02073df0, 0, func_ov008_02073cec },  /* apfnHook */
};
