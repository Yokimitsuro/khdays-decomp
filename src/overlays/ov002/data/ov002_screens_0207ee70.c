/* ov002 screen descriptors, 0x0207ee70-0x0207ee98.
 *
 * 2 records of the shape Ov002_OpenPanelScreen takes: a class id whose high half
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

extern void func_ov002_02065cc8(void);
extern void func_ov002_02065e0c(void);
extern void func_ov002_02066a80(void);
extern void func_ov002_02066ba8(void);

Ov002ScreenDesc data_ov002_0207ee70 = {
    0x0e0037, func_ov002_02065cc8, func_ov002_02065e0c, 44, 0,
};

Ov002ScreenDesc data_ov002_0207ee84 = {
    0x0e0039, func_ov002_02066a80, func_ov002_02066ba8, 148, 0,
};
