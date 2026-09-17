/* ov025 page hooks data_ov025_020b54b8, 0x020b54b8-0x020b54f8 (.data): the day list of page B (Ov025_ScrollList_Open 020ae6f0 / Release 020ae998 / per-frame 020aea2c, 0x2e8-byte Ov025ScrollList; leave Ov025_ScrollList_Leave 020aebc8).
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

extern void WM_EndKeySharing_0x020aebbc(void);
extern void func_ov025_020ae6f0(void);
extern void func_ov025_020ae998(void);
extern void func_ov025_020aea2c(void);
extern void func_ov025_020aea98(void);
extern void func_ov025_020aeaec(void);
extern void func_ov025_020aeb44(void);
extern void func_ov025_020aeb80(void);
extern void func_ov025_020aebc8(void);

Ov008PageHooks data_ov025_020b54b8 = {
    func_ov025_020ae6f0,  /* pfnOpen */
    func_ov025_020ae998,  /* pfnStep */
    func_ov025_020aea2c,  /* pfnClose */
    744,  /* nStateSize */
    { func_ov025_020aea98, func_ov025_020aeaec, func_ov025_020aeb44, func_ov025_020aeb80, WM_EndKeySharing_0x020aebbc, func_ov025_020aebc8, 0, 0, 0, 0, 0, func_ov025_020aebc8 },  /* apfnHook */
};
