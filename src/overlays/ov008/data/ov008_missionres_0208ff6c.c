/* ov008 mission resource descriptor data_ov008_0208ff6c, 0x0208ff6c-0x0208ff78 (.rodata).
 *
 * Opens a mission list (0205652c) from the msl resource path, the selector
 * substituted for the ampersand, and the list kind: mission list kind 5 for the reward scan (02089e94).
 */

typedef struct Ov008MissionResourceDescriptor {
    const char *pResourcePath; /* 0x00: "UI/cm/msl_&.msi.z", & = the selector */
    int nSelector;             /* 0x04 */
    int nListKind;             /* 0x08 */
} Ov008MissionResourceDescriptor;

extern char data_ov008_02090ed4;

const Ov008MissionResourceDescriptor data_ov008_0208ff6c = {
    &data_ov008_02090ed4,  /* pResourcePath */
    0,  /* nSelector */
    5,  /* nListKind */
};
