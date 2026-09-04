/* ov002 screen descriptors, 0x0207e880-0x0207e8a8.
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

extern void func_ov002_02052998(void);
extern void func_ov002_020529cc(void);
extern void func_ov002_020532a8(void);
extern void func_ov002_020533dc(void);

Ov002ScreenDesc data_ov002_0207e880 = {
    0x0e003e, func_ov002_02052998, func_ov002_020529cc, 24, 0,
};

Ov002ScreenDesc data_ov002_0207e894 = {
    0x0e003b, func_ov002_020532a8, func_ov002_020533dc, 296, 0,
};
