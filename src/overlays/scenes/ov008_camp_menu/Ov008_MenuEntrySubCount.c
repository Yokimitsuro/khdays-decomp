/* Returns the number of sub-entries of a menu table entry. */

#include "nitro/types.h"

extern void Ov008_GetMenuContext(void);

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

int Ov008_MenuEntrySubCount(int index)
{
    Ov008_GetMenuContext();
    return gOv008ConfigSettings[index].nSubCount;
}
