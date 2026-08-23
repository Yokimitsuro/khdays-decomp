#pragma opt_strength_reduction off
/*
 * Ov002_SceneDrawEntryLines - draw the up-to-three entry lines into the panel's
 * lower box and flush it.
 *
 * Nothing is drawn at all while the box is empty. The three strings live back to
 * back at +0x7c4; the first empty one ends the run, and each line sits sixteen
 * pixels below the one above it.
 *
 * ARM.
 */

extern int data_ov002_0207f624;

extern void func_02030278(void *pSurface, int nX, int nY, int nKind, int nText,
                          int nFlags);
extern void func_020300f8(void *pSurface);

void func_ov002_0205eaf0(void)
{
    int i;
    int nY;
    int *ctx;
    int nText;

    ctx = *(int **)&data_ov002_0207f624;
    if (*(int *)((char *)ctx + 0x7e0) <= 0) {
        return;
    }

    nY = 3;
    for (i = 0; i < 3; i++) {
        nText = *(int *)((char *)ctx + i * 4 + 0x7c4);
        if (nText == 0) {
            break;
        }
        func_02030278((char *)ctx + 0x734, 0, nY, 8, nText, 0);
        nY += 0x10;
    }
    func_020300f8((char *)ctx + 0x734);
}
