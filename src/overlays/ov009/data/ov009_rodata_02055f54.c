/* ov009 .rodata 0x02055f54-0x02055f6c: menu header limits and the menu object tracker config (func_ov009_0204dc00). */

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

/* The two header limits of the menu (first 12, second 2). */
const struct {
    unsigned short first;
    unsigned short second;
} data_ov009_02055f54 = { 12, 2 };

extern void func_ov009_0204db68(void);
extern void func_ov009_0204db78(void);

/* Read by func_ov009_0204dc00. */
const ResourceTrackerConfig data_ov009_02055f58 = { 256, 32, 32, func_ov009_0204db68, func_ov009_0204db78 };
