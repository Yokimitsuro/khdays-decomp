/* func_ov025_020af470 -- Ov008_StepPageBSlide: per-frame step of page B's slide.
 * While the entry is busy the slide tween is sampled into the panel offset and the
 * sub screen brightness follows the offset (>> 12); otherwise brightness 0.  A
 * closing panel (state 2) whose tween has finished (bit 2 of the tween word) and
 * whose transfer word is clear loads the sub background, rebuilds the entry and
 * refreshes; an opening panel (state 1) whose tween has finished returns to idle.
 * The done flag is a 1-bit field (extract + movs), not a mask test.
 */
typedef unsigned char u8;

typedef struct Ov008PageB {
    u8  pad_000[0x10];
    u8  tween[0x18];          /* 0x010: slide tween; +0x18 (=0x28) holds the state bits */
    unsigned int nTweenPad : 2; /* 0x028 */
    unsigned int bTweenDone : 1;  /* bit 2 = finished */
    unsigned int nTweenRest : 29;
    int nOffset;              /* 0x02c */
    u8  pad_030[0x1f0 - 0x30];
    int nTransfer;            /* 0x1f0 */
    u8  pad_1f4[4];
    int nPanelState;          /* 0x1f8 */
} Ov008PageB;

#define PANEL_IDLE    0
#define PANEL_OPENING 1
#define PANEL_CLOSING 2

extern Ov008PageB *func_ov025_02084b14(void);                 /* Ov008_GetPageB */
extern int func_ov025_020af364(void);                         /* Ov008_IsEntryBusyOrInactive */
extern void func_0203602c(void *pTween, int *pValue);         /* Tween_Sample */
extern int func_ov025_020af398(void);                         /* panel offset >> 12 */
extern void func_0201e3cc(int nBrightness);                   /* SetMasterBrightnessSub */
extern void func_ov025_020af608(int nWhich);                  /* Ov008_LoadMenuSubBg2 */
extern void func_ov025_020af34c(void);
extern void func_ov025_020af408(void);

void func_ov025_020af470(void)
{
    Ov008PageB *pPage = func_ov025_02084b14();
    int nBrightness;

    if (func_ov025_020af364() == 0) {
        nBrightness = 0;
    } else {
        func_0203602c(pPage->tween, &pPage->nOffset);
        nBrightness = func_ov025_020af398();
    }
    func_0201e3cc(nBrightness);
    if (pPage->nPanelState == PANEL_CLOSING && pPage->bTweenDone != 0
        && pPage->nTransfer == 0) {
        func_ov025_020af608(0);
        func_ov025_020af34c();
        func_ov025_020af408();
    }
    if (pPage->nPanelState == PANEL_OPENING) {
        if (pPage->bTweenDone != 0) {
            pPage->nPanelState = PANEL_IDLE;
        }
    }
}
