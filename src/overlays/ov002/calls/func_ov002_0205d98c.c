/*
 * Ov002_PanelSetSecondaryFlag - turn the panel's secondary view on or off from
 * wherever the cursor currently is.
 *
 * What that means depends on the ring the cursor sits on. On the ring that owns
 * the flag, clearing it walks the cursor home and re-applies it there. On the
 * rings that only observe the flag, setting it moves to the view that shows it.
 * On the grid the flag is stored and the row is refreshed in place, and the
 * first list does the same only while the grid still has entries - when it does
 * not, the flag is cleared instead and the cursor is offered the observing view.
 *
 * Nothing happens when the flag already holds the requested value.
 *
 * THUMB.
 */

typedef unsigned char u8;

typedef struct {
    u8 bKind;                           /* +0x000 */
    u8 bMode;                           /* +0x001 */
    u8 pad0002[0xe];
    int nState;                         /* +0x010 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern int func_ov002_0205a3f0(int *pOut, int nIndex);
extern int func_ov002_0205a4a0(void);
extern void func_ov002_0205d214(int nTarget, int nValue);
extern void func_ov002_0205bff4(int nFrom, int nTo);

void func_ov002_0205d98c(int nValue)
{
    Ov002PanelSession *s;
    int nRow;

    s = data_ov002_0207f620;
    switch (func_ov002_0205a3f0(&nRow, s->bMode)) {
    case 4:
        if (nValue == 0) {
            func_ov002_0205d214(0, 2);
            func_ov002_0205bff4(s->bKind, 0);
        }
        break;

    case 0:
    case 3:
    case 5:
        if (nValue != 0) {
            func_ov002_0205d214(9, 2);
        }
        break;

    case 1:
        if (s->nState != nValue) {
            s->nState = nValue;
            func_ov002_0205d214(s->bMode, -1);
        }
        break;

    case 2:
        if (func_ov002_0205a4a0() > 0) {
            if (s->nState != nValue) {
                s->nState = nValue;
                func_ov002_0205d214(s->bMode, -1);
            }
        } else {
            s->nState = 0;
            if (nValue != 0) {
                func_ov002_0205d214(9, 2);
            }
        }
        break;
    }
}
