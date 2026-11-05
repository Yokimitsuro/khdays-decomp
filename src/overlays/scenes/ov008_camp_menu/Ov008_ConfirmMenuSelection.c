/* Ov008_ConfirmMenuSelection -- Ov008_ConfirmMenuSelection (196 B, 10 relocs).
 * Confirms the currently highlighted item (ctx->sel at 0x4c). Resolves the item via
 * Ov008_MenuEntrySubCount(sel) and gates on two stride-0x14 tables indexed by sel: bail silently if
 * the entry's lock state (gOv008ConfigSettings[sel].nState) is set (locked); if its enabled flag (.bEnabled) is clear
 * (unavailable) play cue (PlaySound(0,4)) + refresh and return. Otherwise back up the whole
 * 0x34-byte selection block (0x4c->0x80), decrement the selected item's count and recompute it
 * through Ov008_ClampWrapIndex, then PlaySound(0,0) + Ov008_RefreshMenuPage() refresh.
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

extern Ov008SelCtx *Ov008_GetMenuContext(void);
extern int  Ov008_MenuEntrySubCount(int index);
extern int  Ov008_ClampWrapIndex(int a, int b, int c);
extern void Ov008_RefreshMenuPage(void);
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

extern Ov008ConfigSetting gOv008ConfigSettings[];

void Ov008_ConfirmMenuSelection(void)
{
    Ov008SelCtx *ctx = Ov008_GetMenuContext();
    s16 *p = &ctx->sel;
    int r = Ov008_MenuEntrySubCount((u16)ctx->sel);
    int idx = ctx->sel;

    if (gOv008ConfigSettings[idx].nState != 0) {
        return;
    }
    if (gOv008ConfigSettings[idx].bEnabled == 0) {
        PlaySound(0, 4);
        Ov008_RefreshMenuPage();
        return;
    }
    MI_CpuCopy8(p, &ctx->field80, 0x34);
    (p + 1)[p[0]] -= 1;
    *(p + p[0] + 1) = Ov008_ClampWrapIndex(*(p + p[0] + 1), 0, r);
    PlaySound(0, 0);
    Ov008_RefreshMenuPage();
}
