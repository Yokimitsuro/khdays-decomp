/*
 * Ov002_TickSceneFadeIn - one frame of the scene's fade-in state.
 *
 * The mirror of Ov002_TickSceneFadeOut. Does nothing while bit 2 of the
 * context flags is set. Otherwise it winds the fade timer at +0x04 down by the
 * per-frame step, runs the scene update, and once the timer drops to 0x100 or
 * below it clears bit 1, selects Ov002_BeginSceneSetup as the next state and -
 * unless bit 3 says otherwise - blanks the main screen. It then pushes the
 * master brightness at +0x08 to the sub screen under the same bit 3, winds
 * that brightness down and clamps it at -0x10000.
 *
 * ARM. As in the fade-out, the result is seeded to null before the guard so
 * both exits return the same register, which is what makes the guard a
 * predicated early return.
 */

typedef void (*Ov002StateFn)(void);

extern int func_02023c40(void);        /* frame-rate flag, 1 when running 60Hz */
extern void func_ov002_02051664(void); /* per-frame scene update */
extern void func_0201e374(int nLevel); /* master brightness, main screen */
extern void func_0201e3cc(int nLevel); /* master brightness, sub screen */
extern void func_ov002_02051318(void); /* the state entered once faded in */

extern int data_ov002_0207f600;        /* slot holding the scene context */

Ov002StateFn func_ov002_02051438(void)
{
    Ov002StateFn pNext;
    int nStep;

    pNext = 0;
    if ((*(unsigned int *)data_ov002_0207f600 & 4) != 0) {
        return pNext;
    }

    nStep = func_02023c40() == 1 ? 0xc00 : 0x800;
    *(int *)(data_ov002_0207f600 + 4) =
        *(int *)(data_ov002_0207f600 + 4) - nStep;
    func_ov002_02051664();

    if (*(int *)(data_ov002_0207f600 + 4) <= 0x100) {
        *(unsigned int *)data_ov002_0207f600 =
            *(unsigned int *)data_ov002_0207f600 & ~2;
        pNext = func_ov002_02051318;
        if ((*(unsigned int *)data_ov002_0207f600 & 8) == 0) {
            func_0201e374(-0x10);
        }
    }

    if ((*(unsigned int *)data_ov002_0207f600 & 8) == 0) {
        func_0201e3cc(*(int *)(data_ov002_0207f600 + 8) >> 12);
    }

    nStep = func_02023c40() == 1 ? 0x3000 : 0x1800;
    *(int *)(data_ov002_0207f600 + 8) =
        *(int *)(data_ov002_0207f600 + 8) - nStep;
    if (*(int *)(data_ov002_0207f600 + 8) < -0x10000) {
        *(int *)(data_ov002_0207f600 + 8) = -0x10000;
    }
    return pNext;
}
