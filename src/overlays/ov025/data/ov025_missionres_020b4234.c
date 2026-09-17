/* ov025 mission resource descriptor data_ov025_020b4234, 0x020b4234-0x020b4240 (.rodata).
 *
 * Opens a mission list (Ov025_InitMissionList 0208a13c) from the resource
 * path, the selector substituted for the ampersand, and the list kind: UI/cm/msl_&.msi.z kind 5, the mission list of the reports page (Ov025_Reports_CountUnlocked 0209f860; kind 6 patched in for the challenges).
 */

typedef struct Ov008MissionResourceDescriptor {
    const char *pResourcePath; /* 0x00: the msl / list resource path, & = the selector */
    int nSelector;             /* 0x04 */
    int nListKind;             /* 0x08 */
} Ov008MissionResourceDescriptor;

extern char data_ov025_020b51e4;

const Ov008MissionResourceDescriptor data_ov025_020b4234 = {
    &data_ov025_020b51e4,  /* pResourcePath */
    0,  /* nSelector */
    5,  /* nListKind */
};
