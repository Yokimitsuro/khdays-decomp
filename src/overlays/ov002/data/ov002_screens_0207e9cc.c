/* ov002 screen descriptors, 0x0207e9cc-0x0207e9f4.
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

extern void func_ov002_02058f00(void);
extern void func_ov002_02058fbc(void);
extern void func_ov002_02059d78(void);
extern void func_ov002_02059dc8(void);

Ov002ScreenDesc data_ov002_0207e9cc = {
    0x0e0036, func_ov002_02058f00, func_ov002_02058fbc, 392, 0,
};

Ov002ScreenDesc data_ov002_0207e9e0 = {
    0x0e0034, func_ov002_02059d78, func_ov002_02059dc8, 32, 0,
};
