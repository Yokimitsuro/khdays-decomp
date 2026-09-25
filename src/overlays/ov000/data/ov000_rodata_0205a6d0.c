/* ov000 .rodata 0x0205a6d0-0x0205a6f4: the save-screen layout template and its resource tracker config. */

typedef void (*TrackerCallback)(void);

/* Allocation config of a resource tracker: three pool capacities and the two
 * callbacks the tracker runs on its entries and nodes. */
typedef struct ResourceTrackerConfig {
    unsigned int nEntryCapacity;     /* 0x00 */
    unsigned int nNodeCapacity;      /* 0x04 */
    unsigned int nAuxCapacity;       /* 0x08 */
    TrackerCallback pfnEntry;        /* 0x0c */
    TrackerCallback pfnNode;         /* 0x10 */
} ResourceTrackerConfig;

/* Layout template copied by func_ov000_0204fdac: the save-screen object layout
 * ("UI/cm/sav_o_000.pobj.z"), mode 2. */
typedef struct LayoutTemplate {
    const char *pszLayout;  /* 0x00 */
    int nMode;              /* 0x04 */
    int aParam[2];          /* 0x08 */
} LayoutTemplate;

extern char data_ov000_0205aa48;  /* "UI/cm/sav_o_000.pobj.z" */

const LayoutTemplate data_ov000_0205a6d0 = { &data_ov000_0205aa48, 2, { 0, 0 } };

extern void func_ov000_02052fbc(void);
extern void func_ov000_02052fcc(void);

/* Read by func_ov000_0204f838. */
const ResourceTrackerConfig data_ov000_0205a6e0 = { 256, 8, 12, func_ov000_02052fbc, func_ov000_02052fcc };
