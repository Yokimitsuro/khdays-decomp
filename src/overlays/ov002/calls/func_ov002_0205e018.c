/*
 * Ov002_PanelRefreshRing - rebuild the ring the cursor is on after something
 * changed underneath it.
 *
 * The slots are rebuilt first, and then the ring the classifier names is
 * repainted: the two list rings repaint their group and redraw the span strip
 * that covers them, the cached-entry ring repaints its entry, and the mode that
 * owns its own rows redraws them. All three of the rings that read the loaded
 * mask fall back to closing the panel down when that mask is empty. The slot
 * ring either re-applies a cursor that has nowhere to sit or refreshes its
 * header.
 *
 * The row for the current kind is repainted last, whatever happened above.
 *
 * THUMB.
 */

typedef unsigned char u8;

typedef struct {
    u8 bKind;                           /* +0x000 */
    u8 bMode;                           /* +0x001 */
    u8 pad0002[0x4aa];
    u8 bListRowBase;                    /* +0x4ac */
    u8 bListRowOffset;                  /* +0x4ad */
    u8 pad04ae[2];
    int nLoadedMask;                    /* +0x4b0 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern int func_ov002_0205a3f0(int *pOut, int nIndex);
extern int func_ov002_0205a7b8(void);
extern void func_ov002_0205a924(int nFirst, int nLast, int nGroup, int nKind);
extern void func_ov002_0205ae08(int nSource, int nFlag, int bSecond);
extern void func_ov002_0205b7dc(int nMode, int nKind, int nValue);
extern void func_ov002_0205bbbc(int nMode);
extern void func_ov002_0205bff4(int nFrom, int nTo);
extern void func_ov002_0205c6f4(int nMode);
extern void func_ov002_0205c87c(int nRow);
extern void func_ov002_0205c9c4(void);
extern void func_ov002_0205cab0(void);
extern void func_ov002_0205d96c(int nValue);
extern int func_ov002_020575d0(void);

void func_ov002_0205e018(void)
{
    Ov002PanelSession *s;
    int nRow;
    int bSecond;
    int bAvailable;

    s = data_ov002_0207f620;
    func_ov002_0205bbbc(s->bMode);
    switch (func_ov002_0205a3f0(&nRow, s->bMode)) {
    case 2:
        if (func_ov002_020575d0() != 0 || s->nLoadedMask != 0) {
            func_ov002_0205c6f4(s->bMode);
            func_ov002_0205a924(nRow + 1,
                                s->bListRowBase + s->bListRowOffset, 7, 0xb);
        } else {
            func_ov002_0205d96c(-1);
        }
        break;

    case 3:
        if (s->nLoadedMask != 0) {
            func_ov002_0205c87c(nRow);
            func_ov002_0205a924(s->bListRowBase + nRow + 1,
                                s->bListRowBase + s->bListRowOffset, 7, 0xb);
        } else {
            func_ov002_0205d96c(-1);
        }
        break;

    case 5:
        if (s->nLoadedMask != 0) {
            func_ov002_0205cab0();
        } else {
            func_ov002_0205d96c(-1);
        }
        break;

    case 0:
        if (s->nLoadedMask == 0 && s->bKind == 2) {
            func_ov002_0205bff4(s->bKind, 0);
            break;
        }
        if (s->bKind == 2) {
            bSecond = 1;
        } else {
            bSecond = 0;
        }
        if (func_ov002_0205a7b8() != 0) {
            bAvailable = 1;
        } else {
            bAvailable = 0;
        }
        func_ov002_0205ae08(4, bAvailable, bSecond);
        break;

    case 4:
        func_ov002_0205c9c4();
        break;
    }
    func_ov002_0205b7dc(s->bMode, s->bKind, 0);
}
