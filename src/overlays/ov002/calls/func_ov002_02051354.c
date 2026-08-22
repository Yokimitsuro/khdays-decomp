/*
 * Ov002_TickSceneFadeOut - one frame of the scene's fade-out state.
 *
 * Does nothing while bit 2 of the context flags is set. Otherwise it advances
 * the fade timer at +0x04 by the per-frame step, runs the scene update, and
 * once the timer reaches 0xa000 clears bit 0, drops the VBlank callback and
 * selects Ov002_BeginSceneSetup as the next state. It then pushes the master
 * brightness at +0x08 to the sub screen unless bit 3 says otherwise, advances
 * that brightness toward zero and clamps it there.
 *
 * ARM. Returns the next state callback, or null to stay in this one; the
 * result is seeded to null before the guard so both exits return the same
 * register, which is what makes the guard a predicated early return.
 */

typedef void (*Ov002StateFn)(void);

extern int func_02023c40(void);        /* frame-rate flag, 1 when running 60Hz */
extern void func_ov002_02051664(void); /* per-frame scene update */
extern void func_02000fb4(int nSlot, void *pArg);  /* drop a VBlank callback */
extern void func_0201e3cc(int nLevel); /* master brightness, sub screen */
extern void func_ov002_02051318(void); /* the state entered once faded out */

extern char data_ov002_0207e850[];     /* the VBlank callback's cookie */
extern int data_ov002_0207f600;        /* slot holding the scene context */

Ov002StateFn func_ov002_02051354(void)
{
    Ov002StateFn pNext;
    int nStep;

    pNext = 0;
    if ((*(unsigned int *)data_ov002_0207f600 & 4) != 0) {
        return pNext;
    }

    nStep = func_02023c40() == 1 ? 0xc00 : 0x800;
    *(int *)(data_ov002_0207f600 + 4) =
        *(int *)(data_ov002_0207f600 + 4) + nStep;
    func_ov002_02051664();

    if (*(int *)(data_ov002_0207f600 + 4) >= 0xa000) {
        *(unsigned int *)data_ov002_0207f600 =
            *(unsigned int *)data_ov002_0207f600 & ~1;
        pNext = func_ov002_02051318;
        func_02000fb4(1, data_ov002_0207e850);
    }

    if ((*(unsigned int *)data_ov002_0207f600 & 8) == 0) {
        func_0201e3cc(*(int *)(data_ov002_0207f600 + 8) >> 12);
    }

    nStep = func_02023c40() == 1 ? 0x3000 : 0x1800;
    *(int *)(data_ov002_0207f600 + 8) =
        *(int *)(data_ov002_0207f600 + 8) + nStep;
    if (*(int *)(data_ov002_0207f600 + 8) > 0) {
        *(int *)(data_ov002_0207f600 + 8) = 0;
    }
    return pNext;
}
