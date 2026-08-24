/*
 * Ov002_SceneCrawlStep - the step that types the crawl out and then moves on.
 *
 * The entry the scene names first is selected, and while any of the three
 * blocking hardware flags is up nothing happens but the idle wait. Otherwise a
 * fade of kind 2 with its low bit set stops the frame, and when it does not, one
 * character is typed. The frame the crawl reports finished the screen is either
 * rebuilt around the current entry and its tag tracker armed, or - when there is
 * nothing left to draw - the tracker is armed on its own; either way the scene
 * moves to state 4 and hands back the step that runs from there. The object
 * graphics block is queued unless the crawl asked to be left alone, and the entry
 * the scene names second is selected on the way out.
 *
 * ARM. Twin of func_ov002_0205ef18, which hands this step back.
 */

extern int data_ov002_0207f624;
extern unsigned short data_0204c190;

extern int func_02023c40(void);
extern int func_02023c50(void);

extern void func_ov002_020539f4(int nKey);
extern void func_ov002_0205ed24(void);
extern int func_ov002_0205e9e8(int nCount);
extern void func_ov002_0205eaf0(void);
extern void func_ov002_0205eba4(int nEntry);
extern int func_ov002_020536bc(int nTag);
extern void func_ov002_0205376c(int nEntry, int nKey);
extern void func_ov002_020536dc(int nEntry, int bArmed);
extern void func_ov002_0205ec50(int bArmed);
extern void func_020300f8(int nBlock);
extern int func_ov002_0205f084(void);

void *func_ov002_0205efb4(void)
{
    /* The declaration order is load-bearing: mwccarm hands out the
     * callee-saved registers by rank here, and the context must not
     * come first. */
    void *pNext;
    int *ctx;
    int nEntry;

    pNext = 0;
    ctx = *(int **)&data_ov002_0207f624;
    func_ov002_020539f4(*(int *)((char *)ctx + 0x69c));

    if ((data_0204c190 & 0x83) != 0) {
        func_ov002_0205ed24();
    } else {
        if (func_02023c40() != 2 || (func_02023c50() & 1) == 0) {
            if (func_ov002_0205e9e8(1) == 0) {
                if (ctx[0x1f8] > 0) {
                    func_ov002_0205eaf0();
                    func_ov002_0205eba4(ctx[0x1f7]);
                    nEntry = func_ov002_020536bc(0xd);
                    func_ov002_0205376c(nEntry, *(int *)((char *)ctx + 0x69c));
                    func_ov002_020536dc(nEntry, 1);
                } else {
                    func_ov002_0205ec50(1);
                }
                pNext = func_ov002_0205f084;
                ctx[0] = 4;
            }
            func_020300f8((int)((char *)ctx + 0x6f8));
        }
    }

    func_ov002_020539f4(*(int *)((char *)ctx + 0x6a0));
    return pNext;
}
