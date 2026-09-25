/* ov000 .rodata 0x0205a95c-0x0205a970: resource tracker config. */

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

extern void func_ov000_02059524(void);
extern void func_ov000_0205967c(void);

/* Read by func_ov000_02058e88. */
const ResourceTrackerConfig data_ov000_0205a95c = { 4, 1, 4, func_ov000_02059524, func_ov000_0205967c };
