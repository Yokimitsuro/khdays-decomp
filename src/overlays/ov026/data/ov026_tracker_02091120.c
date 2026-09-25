/* ov026 .rodata 0x02091120-0x02091134: surface/resource tracker config. */

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

extern void func_ov026_0208530c(void);
extern void func_ov026_0208531c(void);

/* Read by func_ov026_0208532c. */
const ResourceTrackerConfig data_ov026_02091120 = { 105, 1, 28, func_ov026_0208530c, func_ov026_0208531c };
