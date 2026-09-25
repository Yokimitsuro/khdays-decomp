/* ov000 .rodata 0x0205a858-0x0205a86c: resource tracker config of the new-game context. */

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

extern void func_ov000_02054648(void);
extern void func_ov000_02054658(void);

/* Read by func_ov000_020532f0. */
const ResourceTrackerConfig data_ov000_0205a858 = { 50, 8, 12, func_ov000_02054648, func_ov000_02054658 };
