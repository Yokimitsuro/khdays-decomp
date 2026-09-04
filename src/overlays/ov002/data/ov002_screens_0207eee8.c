/* ov002 screen descriptors, 0x0207eee8-0x0207eefc.
 *
 * 1 record of the shape Ov002_OpenPanelScreen takes: a class id whose high half
 * selects the group and whose low half is the index, the pair of handlers, the work
 * size the screen needs, and a word that is zero in every record.
 */

typedef void (*Ov002ScreenFn)(void);

typedef struct {
    unsigned int nClassId;
    Ov002ScreenFn pfnOpen;
    Ov002ScreenFn pfnClose;
    int nWorkSize;
    int nReserved;
} Ov002ScreenDesc;

extern void func_ov002_02067708(void);
extern void func_ov002_02067814(void);

Ov002ScreenDesc data_ov002_0207eee8 = {
    0x0e0039, func_ov002_02067708, func_ov002_02067814, 432, 0,
};
