extern int CARDi_ReadRom(int a, int b, int c, int d, int e, int f, int g);
extern int FSi_OnRomReadDone();
extern int *data_0204631c[];

int func_0200aeec(int a, int b, int c, int d) {
    CARDi_ReadRom((int)data_0204631c[1], c, b, d, (int)FSi_OnRomReadDone, a, 1);
    return 6;
}
