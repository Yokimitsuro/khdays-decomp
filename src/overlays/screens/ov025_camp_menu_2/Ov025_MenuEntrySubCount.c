/* Ov025_MenuEntrySubCount -- Ov008_MenuEntrySubCount: the sub-entry count of menu entry nItem
 * (gOv025ConfigSettings); the menu context getter is called first (its result unused). */

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

int Ov025_MenuEntrySubCount(int nItem)
{
    Ov025_GetPageA();
    return gOv025ConfigSettings[nItem].nSubCount;
}
