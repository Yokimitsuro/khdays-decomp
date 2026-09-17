/* ov025 mission resource descriptor data_ov025_020b3870, 0x020b3870-0x020b387c (.rodata).
 *
 * Opens a mission list (Ov025_InitMissionList 0208a13c) from the resource
 * path, the selector substituted for the ampersand, and the list kind: UI/cm/msl_&.msi.z kind 3, the slot list of the records hub (Ov025_Hub_InitEntries 0208b7d0, selector 7 patched in).
 */

typedef struct Ov008MissionResourceDescriptor {
    const char *pResourcePath; /* 0x00: the msl / list resource path, & = the selector */
    int nSelector;             /* 0x04 */
    int nListKind;             /* 0x08 */
} Ov008MissionResourceDescriptor;

extern char data_ov025_020b4b1c;

const Ov008MissionResourceDescriptor data_ov025_020b3870 = {
    &data_ov025_020b4b1c,  /* pResourcePath */
    0,  /* nSelector */
    3,  /* nListKind */
};
