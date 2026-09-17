/* ov025 page hooks data_ov025_020b53c4, 0x020b53c4-0x020b5404 (.data): the mission menu page (020ad180 / 020ad3bc / 020ad50c, 0x570-byte state).
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

extern void WM_EndKeySharing_0x020ad7ac(void);
extern void func_ov025_020ad180(void);
extern void func_ov025_020ad3bc(void);
extern void func_ov025_020ad50c(void);
extern void func_ov025_020ad53c(void);
extern void func_ov025_020ad558(void);
extern void func_ov025_020ad574(void);
extern void func_ov025_020ad5e4(void);
extern void func_ov025_020ad654(void);
extern void func_ov025_020ad6e0(void);
extern void func_ov025_020ad724(void);
extern void func_ov025_020ad768(void);

Ov008PageHooks data_ov025_020b53c4 = {
    func_ov025_020ad180,  /* pfnOpen */
    func_ov025_020ad3bc,  /* pfnStep */
    func_ov025_020ad50c,  /* pfnClose */
    1392,  /* nStateSize */
    { func_ov025_020ad53c, func_ov025_020ad558, func_ov025_020ad574, func_ov025_020ad5e4, func_ov025_020ad654, func_ov025_020ad6e0, 0, 0, func_ov025_020ad724, func_ov025_020ad768, 0, WM_EndKeySharing_0x020ad7ac },  /* apfnHook */
};
