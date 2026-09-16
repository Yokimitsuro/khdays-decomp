/* ov008 mission resource descriptor data_ov008_0208fa10, 0x0208fa10-0x0208fa1c (.rodata).
 *
 * Opens a mission list (0205652c) from the msl resource path, the selector
 * substituted for the ampersand, and the list kind: mission list kind 6 for the mission menu init step (02077b28).
 */

typedef struct Ov008MissionResourceDescriptor {
    const char *pResourcePath; /* 0x00: "UI/cm/msl_&.msi.z", & = the selector */
    int nSelector;             /* 0x04 */
    int nListKind;             /* 0x08 */
} Ov008MissionResourceDescriptor;

extern char data_ov008_020908cc;

const Ov008MissionResourceDescriptor data_ov008_0208fa10 = {
    &data_ov008_020908cc,  /* pResourcePath */
    0,  /* nSelector */
    6,  /* nListKind */
};
