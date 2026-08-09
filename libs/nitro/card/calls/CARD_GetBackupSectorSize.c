/* CARD_GetBackupSectorSize: backup sector size from the card context (+0x1c). */

extern int *data_020464e0;

int CARD_GetBackupSectorSize(void) {
    return *(int *)((char *)data_020464e0 + 0x1c);
}
