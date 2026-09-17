/* ov025 mission resource descriptor data_ov025_020b458c, 0x020b458c-0x020b4598 (.rodata).
 *
 * Opens a mission list (Ov025_InitMissionList 0208a13c) from the resource
 * path, the selector substituted for the ampersand, and the list kind: kind 5 list of the panel page.
 */

typedef struct Ov008MissionResourceDescriptor {
    const char *pResourcePath; /* 0x00: the msl / list resource path, & = the selector */
    int nSelector;             /* 0x04 */
    int nListKind;             /* 0x08 */
} Ov008MissionResourceDescriptor;

extern char data_ov025_020b52fc;

const Ov008MissionResourceDescriptor data_ov025_020b458c = {
    &data_ov025_020b52fc,  /* pResourcePath */
    0,  /* nSelector */
    5,  /* nListKind */
};
