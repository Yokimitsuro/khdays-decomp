/*
 * Ov002_SceneClosePanelStep - the step that folds the panel away.
 *
 * Nothing happens while a fade of kind 2 is still running. Once it is clear the
 * surface is closed a frame at a time; when it reports it has finished the two
 * text contexts are torn down (each only if it was ever opened), the scene state
 * goes back to 0, the two palette entries the panel borrowed are put back, and
 * the step that runs with no panel on screen is handed over.
 *
 * ARM.
 */

typedef unsigned short u16;

extern int data_ov002_0207f624;

extern int func_02023c40(void);
extern int func_02023c50(void);
extern void func_0202ffbc(void *pContext);

extern void func_ov002_0205272c(void *pSurface);
extern void func_ov002_020539f4(int nKey);
extern void func_ov002_02053cd4(int nId);
extern void func_ov002_0205eb78(void);
extern int func_ov002_0205ef08(void);

void *func_ov002_0205f14c(void)
{
    int *ctx;
    void *pNext;

    pNext = 0;
    ctx = *(int **)&data_ov002_0207f624;
    if (func_02023c40() == 2 && (func_02023c50() & 1) == 1) {
        return 0;
    }

    func_ov002_020539f4(*(int *)((char *)ctx + 0x69c));
    func_ov002_0205272c((char *)ctx + 0xc);
    func_ov002_02053cd4(0xb);

    if (ctx[3] == 0) {
        func_ov002_0205eb78();
        if (*(int *)((char *)ctx + 0x7b8) != 0) {
            func_0202ffbc((char *)ctx + 0x6f8);
            *(int *)((char *)ctx + 0x7b8) = 0;
        }
        if (*(int *)((char *)ctx + 0x7bc) != 0) {
            func_0202ffbc((char *)ctx + 0x734);
            *(int *)((char *)ctx + 0x7bc) = 0;
        }
        ctx[0] = 0;
        *(volatile u16 *)0x05000180 = 0;
        *(volatile u16 *)0x05000184 = 0x1f9f;
        pNext = func_ov002_0205ef08;
    }

    func_ov002_020539f4(*(int *)((char *)ctx + 0x6a0));
    return pNext;
}
