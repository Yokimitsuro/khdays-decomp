/* Ov008_MainMenuInit -- main-menu scene constructor, ov008. Grabs the scene heap, brings
 * up the display (Ov008_SetupMenuDisplay) and loads the UI container (Ov008_LoadMenuUi),
 * registers the menu message handler, seeds state (selected -1, region flag), and if a
 * pending sub-scene exists, primes it (Ov008_RecordInputCoords). Returns the top state
 * Ov008_MainMenuTopState. */
extern void *NNSi_FndGetCurrentRootHeap(void);
extern char *data_ov008_02090f00;
extern void  Ov008_SetupMenuDisplay(void);
extern void  Ov008_LoadMenuUi(void);
extern void  StoreGlobalPtrArray4At0c(int, void *);
extern char  Ov008_ReceiveMenuMessage[];
extern void  Ov008_OpenMissionLobby(int);
extern int   Session_IsReady(void);
extern int   Ov008_IsSessionReady(void);
extern int   Ov008_GetPlayerMask(void);
extern void  GameState_ClearFlag(int event);
extern int   Session_GetLocalPlayerIndex(void);
extern char *Slot4_GetIfOccupied(int);
extern void  MI_CpuFill8(void *dst, int val, int size);
extern void  Ov008_BuildMenuListFrom(void *anchor);
extern char *gGameState;
extern int   GameState_IsFlagSet(int);
extern void  Ov008_RecordInputCoords(void *init);
extern void  Ov008_MainMenuTopState(void);

void *Ov008_MainMenuInit(void) {
    char *heap = (char *)NNSi_FndGetCurrentRootHeap();
    char *sel;
    unsigned char init[6];
    data_ov008_02090f00 = heap;
    Ov008_SetupMenuDisplay();
    Ov008_LoadMenuUi();
    StoreGlobalPtrArray4At0c(0xe, Ov008_ReceiveMenuMessage);
    Ov008_OpenMissionLobby(0);
    *(int *)(heap + 0x14) = -1;
    *(unsigned short *)(heap + 0x504c) = 0xffff;
    *(int *)heap = Session_IsReady();
    *(unsigned short *)(heap + 0x2c) = 0;
    if (Ov008_IsSessionReady() != 0) {
        *(unsigned short *)(heap + 0x2c) = Ov008_GetPlayerMask();
    }
    GameState_ClearFlag(0x200a);
    GameState_ClearFlag(0x200c);
    sel = Slot4_GetIfOccupied(Session_GetLocalPlayerIndex());
    MI_CpuFill8(init, 0, 6);
    Ov008_BuildMenuListFrom(gGameState + 0xee0);
    if (sel != 0) {
        init[2] &= ~1;
        *(unsigned short *)(init + 4) = *(int *)(sel + 4);
        init[2] = (init[2] & ~2) | (((unsigned char)GameState_IsFlagSet(0x2010) & 1) << 1);
        init[3] = 0;
        Ov008_RecordInputCoords(init);
    }
    return (void *)Ov008_MainMenuTopState;
}
