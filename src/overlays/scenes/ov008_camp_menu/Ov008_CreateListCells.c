extern char *data_ov008_02090fac;
extern int Ov008_CreateMissionCell(int *mgr, unsigned int res, int slot, int xform, ...);

/* Creates the list frame cell, the scrollbar cell and the twelve row cells. */
void Ov008_CreateListCells(void) {
    char *st = *(char **)&data_ov008_02090fac;
    char *list = st + 0xc57c;
    int handle = *(int *)(st + 0xbfb0);
    int i;
    *(int *)(st + 0xc57c) = Ov008_CreateMissionCell((int *)handle, 0xc, 0, 0, 0);
    *(int *)(list + 4) = Ov008_CreateMissionCell((int *)handle, 0xe, 0, 0, 0);
    for (i = 0; i < 0xc; i++) {
        *(int *)(list + i * sizeof(int) + 8) = Ov008_CreateMissionCell((int *)handle, 0xd, 0, 0, 0);
    }
}
