/*
 * Ov002_HandleHudPageKeys - turn the tutorial pages, or close them.
 *
 * R steps to the next page when there is one. L steps back: the record stream
 * is rewound and replayed up to the start of the previous page, two records a
 * page or four in the wide layout. Start only answers on the last page - it
 * asks for the closing caption, or arms state 3 when the page owns a follow-up
 * - then raises this tutorial's game flag and plays the closing sound.
 *
 * THUMB.
 */

typedef unsigned short u16;

extern int *data_ov002_0207f9fc;
extern u16 data_0204c190;

extern int func_ov002_02067980(void *pStream);
extern void func_ov002_020679b8(void *pStream);
extern void *func_ov002_02067994(void *pStream);
extern void func_ov002_0206736c(u16 nPage);
extern int func_ov002_02062f50(void);
extern void func_ov002_02062e04(int nMode, int nTake);
extern void func_020235a8(int nEvent);
extern void func_02033b78(int nBank, int nCue);

void func_ov002_02067404(void)
{
    int hud;
    int nNext;
    int nStep;
    int i;

    hud = (int)data_ov002_0207f9fc;
    if ((data_0204c190 & 0x100) != 0) {
        nNext = *(u16 *)(hud + 2) + 1;
        if (nNext < func_ov002_02067980((void *)(hud + 0xc))) {
            func_ov002_0206736c((u16)nNext);
            func_02033b78(0, 2);
        }
    } else if ((data_0204c190 & 0x200) != 0) {
        if (*(u16 *)(hud + 2) != 0) {
            if (*(int *)(hud + 0x30) != 0) {
                nStep = 4;
            } else {
                nStep = 2;
            }
            func_ov002_020679b8((void *)(hud + 0xc));
            for (i = 0; i < (*(u16 *)(hud + 2) - 1) * nStep; i++) {
                func_ov002_02067994((void *)(hud + 0xc));
            }
            func_ov002_0206736c((u16)(*(u16 *)(hud + 2) - 1));
            func_02033b78(0, 2);
        }
    } else if ((data_0204c190 & 8) != 0) {
        if (*(u16 *)(hud + 2) + 1 >= func_ov002_02067980((void *)(hud + 0xc))) {
            if (*(int *)(hud + 0x1a8) == 0) {
                if (func_ov002_02062f50() != 0) {
                    func_ov002_02062e04(2, 0);
                } else {
                    func_ov002_02062e04(0, 0);
                }
            } else {
                *(int *)(hud + 0x28) = 3;
            }
            func_020235a8(*(u16 *)hud + 0x3c2b);
            func_02033b78(0, 0xa);
        }
    }
}
