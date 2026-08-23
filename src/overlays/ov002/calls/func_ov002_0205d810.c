/*
 * Ov002_PanelStepCursorBack - move the panel cursor back up one row, or refuse.
 *
 * What "back up" means again depends on what the current mode classifies as.
 * From the top of the slot ring the cursor either goes to row 1, or, when the
 * first cell is empty, the move is refused with a buzz. From the top of the
 * grid it hands over to whichever list has entries. Inside the grid or either
 * list it just steps to the previous row, and the second list is offered as the
 * fallback when the first one has run out above.
 *
 * Every path that does move asks for direction 2; the ones that cannot simply
 * return, which is why so many of the arms end in their own epilogue.
 *
 * THUMB.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 bKind;                           /* +0x000 */
    u8 bMode;                           /* +0x001 */
    u8 pad0002[0x2f];
    u8 bCursorRow;                      /* +0x031 */
    u8 aCells[0x47a];                   /* +0x032 */
    u8 bListRowBase;                    /* +0x4ac */
    u8 bListRowOffset;                  /* +0x4ad */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern void func_02033b24(int nId, int nKind);

extern int func_ov002_0205a3f0(int *pOut, int nIndex);
extern int func_ov002_0205a4a0(void);
extern int func_ov002_0205a4ec(void);
extern void func_ov002_0205d214(int nTarget, int nValue);

void func_ov002_0205d810(void)
{
    Ov002PanelSession *s;
    int nRow;

    s = data_ov002_0207f620;
    switch (func_ov002_0205a3f0(&nRow, s->bMode)) {
    case 0:
        switch (s->bKind) {
        case 1:
            if (s->aCells[0] == 0xff) {
                func_02033b24(0, 4);
                return;
            }
            func_ov002_0205d214(1, 2);
            return;
        case 2:
            if (func_ov002_0205a4a0() > 0) {
                func_ov002_0205d214(4, 2);
                return;
            }
            if (func_ov002_0205a4ec() > 0) {
                func_ov002_0205d214(6, 2);
                return;
            }
            break;
        }
        break;

    case 1:
        if (nRow + 1 < s->bCursorRow) {
            func_ov002_0205d214(s->bMode + 1, 2);
            return;
        }
        break;

    case 2:
        if (nRow >= s->bListRowBase - 1) {
            if (func_ov002_0205a4ec() > 0) {
                func_ov002_0205d214(6, 2);
                return;
            }
            break;
        }
        func_ov002_0205d214(s->bMode + 1, 2);
        return;

    case 3:
        if (nRow + 1 < s->bListRowOffset) {
            func_ov002_0205d214(s->bMode + 1, 2);
        }
        break;
    }
}
