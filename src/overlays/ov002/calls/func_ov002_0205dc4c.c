/*
 * Ov002_PanelSetHelpVisible - show or hide the help strip, and tell the ring
 * the cursor is on about it.
 *
 * The request is forced off while the panel is in its restricted state. If the
 * strip is already where it was asked to be, nothing happens at all; otherwise
 * the new state is stored and the ring the cursor sits on is refreshed: the
 * slot ring rebuilds its labels and, when the strip is going away with the
 * cursor on row 1, re-applies the cursor; the grid either tears the strip down
 * or rebuilds its labels and re-opens it on the row the classifier handed back;
 * the mode that owns its own rows just rebuilds them.
 *
 * THUMB.
 */

typedef unsigned char u8;

typedef struct {
    u8 bKind;                           /* +0x000 */
    u8 bMode;                           /* +0x001 */
    u8 pad0002[0x4a6];
    int nHelpVisible;                   /* +0x4a8 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern int func_ov002_0205a3f0(int *pOut, int nIndex);
extern int func_ov002_020575d0(void);
extern void func_ov002_0205bbbc(int nMode);
extern void func_ov002_0205bff4(int nFrom, int nTo);
extern void func_ov002_0205c57c(void);
extern void func_ov002_0205c624(int nRow);
extern void func_ov002_0205c9c4(void);
extern void func_ov002_0205d96c(int nValue);

void func_ov002_0205dc4c(int nVisible)
{
    Ov002PanelSession *s;
    int nClass;
    int nRow;

    s = data_ov002_0207f620;
    nClass = func_ov002_0205a3f0(&nRow, s->bMode);
    if (func_ov002_020575d0() != 0) {
        nVisible = 0;
    }
    if (s->nHelpVisible == nVisible) {
        return;
    }
    s->nHelpVisible = nVisible;

    switch (nClass) {
    case 0:
        func_ov002_0205bbbc(s->bMode);
        if (nVisible == 0 && s->bKind == 1) {
            func_ov002_0205bff4(s->bKind, 0);
        }
        func_ov002_0205c57c();
        return;

    case 1:
        if (nVisible == 0) {
            func_ov002_0205d96c(-1);
            return;
        }
        func_ov002_0205bbbc(s->bMode);
        func_ov002_0205c624(nRow);
        return;

    case 4:
        func_ov002_0205c9c4();
        return;
    }
}
