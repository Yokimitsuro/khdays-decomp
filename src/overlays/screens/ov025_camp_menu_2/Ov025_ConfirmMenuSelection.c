/* Ov025_ConfirmMenuSelection -- Ov008_ConfirmMenuSelection (196 B, 10 relocs).
 * Confirms the currently highlighted item (ctx->sel at 0x4c). Resolves the item via
 * Ov025_MenuEntrySubCount(sel) and gates on two stride-0x14 tables indexed by sel: bail silently if
 * data_ov025_020b4f69[sel*0x14] is set (locked); if data_ov025_020b4f6a[sel*0x14] is clear
 * (unavailable) play cue (PlaySound(0,4)) + refresh and return. Otherwise back up the whole
 * 0x34-byte selection block (0x4c->0x80), decrement the selected item's count and recompute it
 * through Ov025_ClampWrapIndex, then PlaySound(0,0) + Ov025_RefreshMenuPage() refresh.
 * NOTE: the counts run right after ctx->sel, and the original holds a single base pointer
 * p = &ctx->sel (r6) for the copy source AND the count accesses -- hence the pointer forms
 * (p+1)[p[0]] and *(p+p[0]+1) rather than ctx->counts[ctx->sel] (which would re-base on ctx). */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Ov008SelCtx {
    u8  pad_0000[0x4c];
    s16 sel;            /* 0x4c: highlighted item index */
    s16 counts[0x19];   /* 0x4e: per-item remaining counts */
    u8  field80[0x34];  /* 0x80: backup of the selection block */
} Ov008SelCtx;

extern Ov008SelCtx *Ov025_GetPageA(void);
extern int  Ov025_MenuEntrySubCount(int index);
extern int  Ov025_ClampWrapIndex(int a, int b, int c);
extern void Ov025_RefreshMenuPage(void);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
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

void Ov025_ConfirmMenuSelection(void)
{
    Ov008SelCtx *ctx = Ov025_GetPageA();
    s16 *p = &ctx->sel;
    int r = Ov025_MenuEntrySubCount((u16)ctx->sel);
    int idx = ctx->sel * 0x14;

    if ((&gOv025ConfigSettings->nState)[idx] != 0) {
        return;
    }
    if ((&gOv025ConfigSettings->bEnabled)[idx] == 0) {
        PlaySound(0, 4);
        Ov025_RefreshMenuPage();
        return;
    }
    MI_CpuCopy8(p, &ctx->field80, 0x34);
    (p + 1)[p[0]] -= 1;
    *(p + p[0] + 1) = Ov025_ClampWrapIndex(*(p + p[0] + 1), 0, r);
    PlaySound(0, 0);
    Ov025_RefreshMenuPage();
}
