/* Ov025_DispatchFrom2DTable -- Ov008_DispatchFrom2DTable: pick sub-entry nColumn of menu entry nItem
 * (gOv025ConfigSettings) and hand its id to Ov008_Set_9bec (0209bfcc) for the widget pick; the
 * two context getters are called first (their results unused). */

#include "nitro/types.h"

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

extern void *Ov025_GetPageA(void);                             /* Ov008_GetMenuContext */
extern int   Ov025_GetContext(void);                             /* Ov008_GetContext */
extern void  Ov025_WidgetRef_Init(short *pPick, s16 nId);            /* Ov008_Set_9bec */

void Ov025_DispatchFrom2DTable(short *pPick, short nItem, int nColumn)
{
    Ov025_GetPageA();
    Ov025_GetContext();
    Ov025_WidgetRef_Init(pPick, gOv025ConfigSettings[nItem].aSub[nColumn].nId);
}
