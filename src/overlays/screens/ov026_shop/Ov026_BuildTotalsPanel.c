extern char *data_ov026_02091368;
extern char *gGameState;
extern int Ov026_CreateMissionCell(int *mgr, unsigned int res, int slot, int xform, ...);
extern void Slot_SetVisible(int handle, int cell, int visible);
extern int Ov026_FindEntryById(void *p, int id);
extern void Ov026_SetEntrySlotsVisible(void *p, int cell, int on);

/* Builds the totals panel for the summary tab: copies the two counters out of the save header,
 * creates their two cells and shows them. */
void Ov026_BuildTotalsPanel(void) {
    char *st = *(char **)&data_ov026_02091368;
    char *panel = st + 0xc54c;
    int handle = *(int *)(st + 0xbfb0);
    char *sound = st + 0x2ab0;
    *(short *)(panel + 0x28) = *(unsigned short *)(*(char **)&gGameState + 0x196a);
    *(short *)(panel + 0x2a) = *(unsigned short *)(*(char **)&gGameState + 0x1968);
    *(int *)(st + 0xc54c) = Ov026_CreateMissionCell((int *)handle, 0x13, 0, 0x24000, 0xa000);
    *(int *)(panel + 4) = Ov026_CreateMissionCell((int *)handle, 0x14, 0, 0x4c000, 0xa000);
    Slot_SetVisible(handle, *(int *)(st + 0xc54c), 1);
    Slot_SetVisible(handle, *(int *)(panel + 4), 1);
    Ov026_SetEntrySlotsVisible(sound, Ov026_FindEntryById(sound, 1), 1);
}
