/* Ov008_CancelMenuSelection -- Ov008_CancelMenuSelection (196 B, 10 relocs).
 * Twin of Ov008_ConfirmMenuSelection (Ov008_ConfirmMenuSelection): the un-select action for the
 * highlighted item (ctx->sel). Same gating on the entry's lock state / enabled flag (gOv008ConfigSettings[sel]) and the same held
 * base pointer p = &ctx->sel, but it INCREMENTS the item's count (restoring it) instead of
 * decrementing, and on the unavailable path it refreshes first (Ov008_RefreshMenuPage) then plays
 * the cue (PlaySound(0,4)). See the confirm twin for the addressing-form notes. */

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

void Ov008_CancelMenuSelection(void)
{
    Ov008SelCtx *ctx = Ov008_GetMenuContext();
    s16 *p = &ctx->sel;
    int r = Ov008_MenuEntrySubCount((u16)ctx->sel);
    int idx = ctx->sel;

    if (gOv008ConfigSettings[idx].nState != 0) {
        return;
    }
    if (gOv008ConfigSettings[idx].bEnabled == 0) {
        Ov008_RefreshMenuPage();
        PlaySound(0, 4);
        return;
    }
    MI_CpuCopy8(p, &ctx->field80, 0x34);
    (p + 1)[p[0]] += 1;
    *(p + p[0] + 1) = Ov008_ClampWrapIndex(*(p + p[0] + 1), 0, r);
    PlaySound(0, 0);
    Ov008_RefreshMenuPage();
}
