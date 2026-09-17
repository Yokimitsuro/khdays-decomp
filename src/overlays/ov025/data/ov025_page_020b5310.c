/* ov025 page hooks data_ov025_020b5310, 0x020b5310-0x020b5350 (.data): the mission list page (020a8b28 / 020a8d50 / 020a8f58, 0x508-byte Ov008MissionList; back Ov025_MissionList_Back 020a92b0, cursor Ov025_MissionList_CursorPrev / Next 020a93a0 / 020a93fc).
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

extern void func_ov025_020a8b28(void);
extern void func_ov025_020a8d50(void);
extern void func_ov025_020a8f58(void);
extern void func_ov025_020a8fc8(void);
extern void func_ov025_020a9090(void);
extern void func_ov025_020a913c(void);
extern void func_ov025_020a91a4(void);
extern void func_ov025_020a920c(void);
extern void func_ov025_020a92b0(void);
extern void func_ov025_020a93a0(void);
extern void func_ov025_020a93fc(void);

Ov008PageHooks data_ov025_020b5310 = {
    func_ov025_020a8b28,  /* pfnOpen */
    func_ov025_020a8d50,  /* pfnStep */
    func_ov025_020a8f58,  /* pfnClose */
    1288,  /* nStateSize */
    { func_ov025_020a8fc8, func_ov025_020a9090, func_ov025_020a913c, func_ov025_020a91a4, func_ov025_020a920c, func_ov025_020a92b0, 0, 0, func_ov025_020a93a0, func_ov025_020a93fc, 0, func_ov025_020a92b0 },  /* apfnHook */
};
