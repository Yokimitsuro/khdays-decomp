/* ov025 mission resource descriptor data_ov025_020b3940, 0x020b3940-0x020b394c (.rodata).
 *
 * Opens a mission list (Ov025_InitMissionList 0208a13c) from the resource
 * path, the selector substituted for the ampersand, and the list kind: the main menu's list (Ov008_MainMenu_StateTick 0208d730, kind and selector patched by the scene state; 0208ccbc).
 */

typedef struct Ov008MissionResourceDescriptor {
    const char *pResourcePath; /* 0x00: the msl / list resource path, & = the selector */
    int nSelector;             /* 0x04 */
    int nListKind;             /* 0x08 */
} Ov008MissionResourceDescriptor;

extern char data_ov025_020b4ca0;

const Ov008MissionResourceDescriptor data_ov025_020b3940 = {
    &data_ov025_020b4ca0,  /* pResourcePath */
    0,  /* nSelector */
    6,  /* nListKind */
};
