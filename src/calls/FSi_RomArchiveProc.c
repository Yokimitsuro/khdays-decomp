extern void CARD_LockRom(unsigned short lockId);
extern void CARD_UnlockRom(unsigned short lockId);
extern int *data_0204631c[];

int FSi_RomArchiveProc(void *arc, int command, void *param) {
    switch (command) {
    case 9:
        CARD_LockRom((unsigned short)(int)data_0204631c[0]);
        return 0;
    case 10:
        CARD_UnlockRom((unsigned short)(int)data_0204631c[0]);
        return 0;
    case 1:
        return 4;
    default:
        return 8;
    }
}
