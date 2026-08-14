/* Refresh the panel for whatever mode it is currently in.
 *
 * First the list index is clamped to the live entry count, stepping back one
 * when the count is positive. Then the mode is classified and dispatched: class
 * 0 refreshes the row-4 header, except that kind 2 with both lists empty applies
 * a cursor move instead; class 2 recomputes the mode and kind from the list
 * index, repaints the list group, pushes the row widget, reopens the tracker if
 * it is closed, and runs the kind repaint. Either way it ends by handing the
 * mode on.
 *
 * The list index is an unsigned char, so it promotes to int and the divisions
 * by six come out signed -- magic multiply plus the lsr #31 correction -- even
 * though the value can never be negative. Writing them as unsigned loses that.
 */
typedef unsigned char u8;

typedef struct {
    u8 bKind;                   /* +0x00 */
    u8 bMode;                   /* +0x01 */
    u8 pad0002;
    u8 bListIndex;              /* +0x03 */
    u8 pad0004[0x4a8];
    u8 bListRowBase;            /* +0x4ac */
    u8 bListRowOffset;          /* +0x4ad */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern int func_ov002_0205a4a0(void);
extern int func_ov002_0205a4ec(void);
extern int func_ov002_0205a3f0(int *pOut, int nMode);
extern int func_ov002_0205a7b8(void);
extern void func_ov002_0205ae08(int nRow, int bEnabled, int bRightAlign);
extern void func_ov002_0205bff4(int nFrom, int nTo);
extern void func_ov002_0205c6f4(int nCode);
extern void func_ov002_0205a924(int a, int b, int c, int d);
extern int func_ov002_020536bc(int nTag);
extern int func_ov002_0205374c(int nHandle);
extern int func_ov002_02053558(int nTag);
extern void func_ov002_020535f0(int nHandle);
extern void func_ov002_0205b7dc(int nMode, int nKind, int nFlag);
extern void func_ov002_0205bbbc(int nMode);

void func_ov002_0205cc44(void) {
    Ov002PanelSession *s = data_ov002_0207f620;
    int nClass;
    int nCount;

    nCount = func_ov002_0205a4a0();
    if (s->bListIndex >= nCount) {
        if (nCount > 0) {
            nCount--;
        }
        s->bListIndex = nCount;
    }

    switch (func_ov002_0205a3f0(&nClass, s->bMode)) {
    case 0:
        if (s->bKind == 2) {
            if (func_ov002_0205a4a0() + func_ov002_0205a4ec() > 0) {
                func_ov002_0205ae08(4, func_ov002_0205a7b8(), 1);
            } else {
                func_ov002_0205bff4(s->bKind, 0);
            }
        } else {
            func_ov002_0205ae08(4, func_ov002_0205a7b8(), 0);
        }
        break;

    case 2:
        s->bMode = s->bListIndex / 6 + 4;
        s->bKind = s->bListIndex % 6;
        func_ov002_0205c6f4(s->bMode);
        func_ov002_0205a924(nClass + 1,
                            s->bListRowBase + s->bListRowOffset, 7, 0xb);
        if (func_ov002_0205374c(func_ov002_020536bc(0xe)) == 0) {
            func_ov002_020535f0(func_ov002_02053558(0x79));
        }
        func_ov002_0205b7dc(s->bMode, s->bListIndex % 6, 0);
        break;
    }

    func_ov002_0205bbbc(s->bMode);
}
