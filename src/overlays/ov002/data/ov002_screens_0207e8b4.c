/* ov002 screen descriptors, 0x0207e8b4-0x0207e8dc.
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

extern void func_ov002_02054d18(void);
extern void func_ov002_02054d38(void);
extern void func_ov002_0205633c(void);
extern void func_ov002_02056808(void);

Ov002ScreenDesc data_ov002_0207e8b4 = {
    0x0e0000, func_ov002_02054d18, func_ov002_02054d38, 8, 0,
};

Ov002ScreenDesc data_ov002_0207e8c8 = {
    0x0e0031, func_ov002_0205633c, func_ov002_02056808, 708, 0,
};
