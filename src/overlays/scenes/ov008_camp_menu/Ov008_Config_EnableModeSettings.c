/* Enables the Preferences page's Mission Mode settings the game has opened: settings 15-18
 * (Friendly Fire, Friendly Lock-ons, Rank Crowns, Handicaps) unless story flag 0x200d is set, and
 * setting 24 (Limit Breaks) when the game state's byte +0x9b0 is. A setting left disabled is drawn
 * as "?" (cfg_&.s record 3). */

#include "nitro/types.h"
#include "game/engine.h"

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
extern u8 *gGameState;

void Ov008_Config_EnableModeSettings(void) {
    if (GameState_IsFlagSet(0x200d) == 0) {
        gOv008ConfigSettings[15].bEnabled = 1;
        gOv008ConfigSettings[16].bEnabled = 1;
        gOv008ConfigSettings[17].bEnabled = 1;
        gOv008ConfigSettings[18].bEnabled = 1;
    }
    if (gGameState[0x9b0] != 0) {
        gOv008ConfigSettings[24].bEnabled = 1;
    }
}
