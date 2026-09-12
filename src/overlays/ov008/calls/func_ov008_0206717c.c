/* func_ov008_0206717c -- Ov008_ToggleOptionFlag: flip game flag 0x2010 from the
 * options list.  With the "reverse" word (+0x1fa4) set the flag is cleared when
 * it was set (target slot 0 -> -1) or set otherwise; without it the polarity is
 * the other way round.  Then, unless a transfer is pending, rebinds the three
 * list callbacks and plays the confirm cue.
 */
typedef unsigned char u8;

typedef struct Ov008MenuContext {
    u8   pad_0000[0x30];
    int  nTransferPending;   /* 0x30 */
    u8   pad_0034[0x1fa4 - 0x34];
    int  bReverse;           /* 0x1fa4 */
} Ov008MenuContext;

typedef struct Ov008ListHooks {
    u8   pad_00[0x14];
    void (*pfnSelect)(void); /* 0x14 */
    void (*pfnCancel)(void); /* 0x18 */
    u8   pad_1c[8];
    void (*pfnDone)(void);   /* 0x24 */
} Ov008ListHooks;

#define FLAG_OPTION 0x2010
#define NO_TARGET   -1

extern Ov008MenuContext *func_ov008_02050cd4(void);            /* Ov008_GetMenuContext */
extern int func_02023588(int nFlag);                            /* GameState_IsFlagSet */
extern void func_020235a8(int nFlag);                           /* GameState_SetFlag */
extern void func_020235bc(int nFlag);                           /* GameState_ClearFlag */
extern void func_ov008_02050970(int nEntry, int nTarget);       /* Ov008_SetTargetSlot */
extern void func_02033b78(int nKind, int nArg);                 /* PlaySound */
extern void func_ov008_02066394(void);
extern void func_ov008_02065f80(void);
extern void func_ov008_0206608c(void);
extern Ov008ListHooks data_ov008_02090380;

void func_ov008_0206717c(void)
{
    Ov008MenuContext *pCtx = func_ov008_02050cd4();

    if (pCtx->bReverse != 0) {
        if (func_02023588(FLAG_OPTION) == 0) {
            func_ov008_02050970(-1, NO_TARGET);
        } else {
            func_ov008_02050970(0, NO_TARGET);
        }
        func_020235a8(FLAG_OPTION);
    } else {
        if (func_02023588(FLAG_OPTION) != 0) {
            func_ov008_02050970(-1, NO_TARGET);
        } else {
            func_ov008_02050970(0, NO_TARGET);
        }
        func_020235bc(FLAG_OPTION);
    }
    if (pCtx->nTransferPending != 0) {
        return;
    }
    data_ov008_02090380.pfnDone = func_ov008_02066394;
    data_ov008_02090380.pfnSelect = func_ov008_02065f80;
    data_ov008_02090380.pfnCancel = func_ov008_0206608c;
    func_02033b78(0, 1);
}
