typedef unsigned char u8;
typedef unsigned short u16;

extern u8 data_0204c240;                /* g_modeAndDayClock */

extern char *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov002_02069454(void);  /* Ov002_TickSessionRequest */
extern void func_02023c30(int nArg);  /* SetGameMode */
extern void func_ov002_0206a0f4(void);  /* Ov002_DropLinkSession */
extern void func_0201e4a8(int nArg0, int nArg1);  /* UnloadOverlaySync */
extern void func_ov002_020697cc(void);  /* Ov002_ClearRosterRow */
extern void func_0202b788(void);  /* EntityManager_ReleaseViews */
extern void func_020235a8(int nFlag);  /* GameState_SetFlag */
extern void func_0202b73c(void);  /* EntityManager_ResetSingleton */
extern void func_ov002_02076924(void);  /* Ov002_ResetNineSlots */
extern void func_ov002_0206da28(void);  /* Ov002_ScheduleRetry */
extern void func_02020a78(int nKind, int nArg);  /* PushSceneRequest */
extern int func_02023588(int nFlag);  /* GameState_IsFlagSet */
extern void func_020235bc(int nFlag);  /* DispatchToHandler */
extern int func_020235d0(int nField, int nWidth);  /* GameState_GetField */
extern void func_020336a4(int nArg);  /* RequestQueue_SetOrPushKind3 */

extern void *func_ov002_02068698(void);
extern void *func_ov002_02068d54(void);
extern void *func_ov002_02068f7c(void);

/* Retires the finished sub-flow and picks the state to run next.
 *
 * Nothing happens at all until the sub-flow reports itself done.  Once it does,
 * its completion hook is taken and run -- its answer is what the rest of this
 * switches on -- the teardown hook is run, the slot is released, and the
 * pending id goes back to -1.
 *
 * What happens then depends on the phase.  In phase nine the hook's answer
 * picks between acknowledging one flag, acknowledging another and handing back
 * to the confirm state, or leaving: outside a linked run leaving tears the
 * scene down and reports -2, and inside one it just hands back.  In phase
 * eleven two flags are cleared if either was set, the panel is armed, and a
 * five-bit field decides whether a stamp is written or the shop is nudged.
 *
 * Every other path just refreshes the caption from nIdleCaptionId and hands
 * back to the idle state.
 *
 * The root fields are, from +0x8ba8: wCaptionId at +2, nPanelArmed at +0xc,
 * nStampValue at +0x10 and nIdleCaptionId at +0x18.  The two hooks live at
 * root +0x8ba0 and +0x8b84.
 */
void *func_ov002_020690cc(void)
{
    char *pRoot;
    char *pScreen;
    int nAnswer;

    pRoot = NNSi_FndGetCurrentRootHeap();
    pScreen = pRoot + 0x8ba8;
    nAnswer = 0;
    if (func_ov002_02069454() == 0) {
        return (void *)nAnswer;
    }

    func_02023c30((u8)*(int *)(pRoot + 0x8b54));
    func_ov002_0206a0f4();

    if (*(int *)(pRoot + 0x8b4c) != -1) {
        if (*(int (**)(void))(pRoot + 0x8ba0) != 0) {
            nAnswer = (*(int (**)(void))(pRoot + 0x8ba0))();
        }
        (*(void (**)(void))(pRoot + 0x8b84))();
        func_0201e4a8(0, *(int *)(pRoot + 0x8b50));
        *(int *)(pRoot + 0x8b4c) = -1;
    }

    func_ov002_020697cc();
    func_0202b788();

    switch (*(int *)(pRoot + 0x8b58)) {
    case 9:
        switch (nAnswer) {
        case 2:
            func_020235a8(0x2088);
            *(u16 *)(pScreen + 2) = (u16)*(int *)(pScreen + 0x18);
            break;
        case 4:
            func_020235a8(0x2087);
            func_0202b73c();
            *(u16 *)(pScreen + 2) = 0;
            *(int *)(pScreen + 0xc) = 0;
            return func_ov002_02068698;
        case 8:
            if ((data_0204c240 & 4) != 0) {
                func_0202b73c();
                *(u16 *)(pScreen + 2) = 0;
                *(int *)(pScreen + 0xc) = 0;
                return func_ov002_02068d54;
            }
            func_0202b73c();
            func_ov002_02076924();
            func_ov002_0206da28();
            func_02020a78(1, 0);
            return (void *)-2;
        }
        break;
    case 0xb:
        if (func_02023588(0x18bd) != 0 || func_02023588(0x18c9) != 0) {
            func_020235bc(0x18bd);
            func_020235bc(0x18c9);
            *(int *)(pScreen + 0xc) = 1;
            if (func_020235d0(0x2080, 5) == 0x1b) {
                *(int *)(pScreen + 0x10) =
                    (func_020235d0(0, 9) == 0x165) ? 0x2711 : 0x2710;
            } else {
                func_020336a4(0x14);
            }
            return func_ov002_02068698;
        }
        *(u16 *)(pScreen + 2) = (u16)*(int *)(pScreen + 0x18);
        break;
    default:
        *(u16 *)(pScreen + 2) = (u16)*(int *)(pScreen + 0x18);
        break;
    }
    return func_ov002_02068f7c;
}
