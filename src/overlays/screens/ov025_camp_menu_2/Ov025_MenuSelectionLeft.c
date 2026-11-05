/* Ov025_MenuSelectionLeft -- Ov008_MenuSelectionLeft: the "left" action on the
 * highlighted item (ctx->sel at 0x4c).  The selection block is backed up first
 * (0x4c -> 0x80, 0x34 bytes).  A locked item (data_ov025_020b4f69[sel*0x14] == 0)
 * moves the highlight to the previous selectable item via Ov025_FindSelectableItem
 * (sel - 1, wrapping, step -1) when one exists; kind 1 decrements the item's count
 * and re-clamps it against Ov025_MenuEntrySubCount(sel) through Ov025_ClampWrapIndex.
 * Either way the cursor cue plays and the menu refreshes.
 */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Ov008SelCtx {
    u8  pad_0000[0x4c];
    s16 sel;            /* 0x4c: highlighted item index */
    s16 counts[0x19];   /* 0x4e: per-item remaining counts */
    u8  field80[0x34];  /* 0x80: backup of the selection block */
} Ov008SelCtx;

#define ITEM_STRIDE 0x14
#define KIND_LOCKED 0
#define KIND_COUNT  1

extern Ov008SelCtx *Ov025_GetPageA(void);
extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);
extern int  Ov025_MenuEntrySubCount(int nIndex);                         /* item max count */
extern int  Ov025_ClampWrapIndex(int nValue, int nMin, int nMax);     /* ClampWrapIndex */
extern int  Ov025_FindSelectableItem(s16 nFrom, int nStep);               /* next selectable item, -1 if none */
extern void Ov025_RefreshMenuPage(void);                               /* menu refresh */
typedef struct Ov008ConfigValue {
    s16 nId;                  /* 0x00 */
    u8  nText;                /* 0x02: its name, a cfg_&.s record */
    u8  nHelpText;            /* 0x03: its help, a cfg_&.s record */
} Ov008ConfigValue;

typedef struct Ov008ConfigSetting {
    s16 nId;                  /* 0x00 */
    u8  nText;                /* 0x02: its name, a cfg_&.s record */
    u8  nHelpText;            /* 0x03: its help, a cfg_&.s record */
    u8  nAnchor;              /* 0x04 */
    u8  nState;               /* 0x05: lock state */
    u8  bEnabled;             /* 0x06: 0 shows it as "?" */
    u8  nSubCount;            /* 0x07: its values; 0 for a heading */
    Ov008ConfigValue aSub[3]; /* 0x08 */
} Ov008ConfigSetting;

extern Ov008ConfigSetting gOv025ConfigSettings[];                    /* the Preferences page's settings */

void Ov025_MenuSelectionLeft(void)
{
    Ov008SelCtx *ctx = Ov025_GetPageA();
    s16 *p = &ctx->sel;
    s16 sel;
    int nNext;

    MI_CpuCopy8(p, &ctx->field80, 0x34);
    sel = ctx->sel;
    switch (gOv025ConfigSettings[sel].nState) {
    case KIND_COUNT:
        (p + 1)[sel] -= 1;
        *(p + p[0] + 1) = Ov025_ClampWrapIndex(*(p + p[0] + 1), 0, Ov025_MenuEntrySubCount((u16)*p));
        break;
    case KIND_LOCKED:
        nNext = Ov025_FindSelectableItem((s16)(sel - 1), -1);
        if (nNext >= 0) {
            *p = nNext;
        }
        break;
    }
    PlaySound(0, 0);
    Ov025_RefreshMenuPage();
}
