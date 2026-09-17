/* ov025 mission resource descriptor data_ov025_020b46c0, 0x020b46c0-0x020b46cc (.rodata).
 *
 * Opens a mission list (Ov025_InitMissionList 0208a13c) from the resource
 * path, the selector substituted for the ampersand, and the list kind: kind 6 list of the mission menu (020ab7b0 family).
 */

typedef struct Ov008MissionResourceDescriptor {
    const char *pResourcePath; /* 0x00: the msl / list resource path, & = the selector */
    int nSelector;             /* 0x04 */
    int nListKind;             /* 0x08 */
} Ov008MissionResourceDescriptor;

extern char data_ov025_020b53b0;

const Ov008MissionResourceDescriptor data_ov025_020b46c0 = {
    &data_ov025_020b53b0,  /* pResourcePath */
    0,  /* nSelector */
    6,  /* nListKind */
};
