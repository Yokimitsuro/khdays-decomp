/* Refresh the three panel row headers for the current kind, then replay the
 * 0x5a sub request and re-select entry 0xb. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 bKind;               /* +0x0 */
    u8 pad0001[0xb];
    int nPrimaryValue;      /* +0xc */
    u8 pad0010[4];
    u16 wPrimaryRow;        /* +0x14 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern int func_ov002_0205a7b8(void);
extern int func_ov002_0205a638(void);
extern void func_ov002_0205ae08(int nSlot, int nValue, int nFlag);
extern int func_ov002_02053558(int nId);
extern void func_ov002_020535a4(int nEntry);
extern void func_ov002_02053cd4(int nId);

void func_ov002_0205c57c(void) {
    Ov002PanelSession *s = data_ov002_0207f620;
    int bItems = (s->bKind == 2);
    int nAvail = func_ov002_0205a7b8();

    func_ov002_0205ae08(4, nAvail != 0, bItems);
    func_ov002_0205ae08(s->wPrimaryRow, s->nPrimaryValue, s->bKind == 0);

    if (s->bKind == 1) {
        func_ov002_0205ae08(3, func_ov002_0205a638(), 1);
    } else {
        func_ov002_0205ae08(3, func_ov002_0205a638(), 0);
    }

    func_ov002_020535a4(func_ov002_02053558(0x5a));
    func_ov002_02053cd4(0xb);
}
