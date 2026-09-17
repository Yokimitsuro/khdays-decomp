/* ov025 screen hooks data_ov025_020b4d4c, 0x020b4d4c-0x020b4d90 (.data): the grid / panel list menu screen (02097eec .. 02098f60, 0x20a0-byte state: select 020984ac, cancel 020985b8, done 020988c0, the B handler 02098ad4).
 */

typedef void (*Ov008HookFn)(void);

/* 0x44-byte screen class: entered / stepped / left through the first three
 * slots by index (the ov008 screen dispatcher 020513bc / 020513f0 family via the
 * slot table data_ov025_020b4ab0); the list menus read pfnSelect / pfnCancel /
 * pfnDone (data_ov025_020b4d4c is rebound by 02099558 / 020995cc). */
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

extern void func_ov025_02097eec(void);
extern void func_ov025_02098214(void);
extern void func_ov025_020983c0(void);
extern void func_ov025_020984ac(void);
extern void func_ov025_020985b8(void);
extern void func_ov025_020986c0(void);
extern void func_ov025_020987c0(void);
extern void func_ov025_020988c0(void);
extern void func_ov025_02098ad4(void);
extern void func_ov025_02098dc4(void);
extern void func_ov025_02098e30(void);
extern void func_ov025_02098e9c(void);
extern void func_ov025_02098f18(void);
extern void func_ov025_02098f60(void);

Ov008ScreenHooks data_ov025_020b4d4c = {
    func_ov025_02097eec,  /* pfnOpen */
    func_ov025_02098214,  /* pfnStep */
    func_ov025_020983c0,  /* pfnClose */
    0,  /* nFlags */
    8352,  /* nStateSize */
    func_ov025_020984ac,  /* pfnSelect */
    func_ov025_020985b8,  /* pfnCancel */
    { func_ov025_020986c0, func_ov025_020987c0 },  /* apfnAux */
    func_ov025_020988c0,  /* pfnDone */
    { func_ov025_02098ad4, 0, func_ov025_02098e9c, func_ov025_02098dc4, func_ov025_02098e30, func_ov025_02098f18, func_ov025_02098f60 },  /* apfnHook */
};
