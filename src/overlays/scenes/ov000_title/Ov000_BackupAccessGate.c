#pragma thumb on
/* Ov000_BackupAccessGate -- Scene 1 (boot/logo) backup-access gate, ov000. THUMB.
 * Unlocks the save (CARD) backup for the current device id (data_0204be10),
 * samples whether a follow-up condition holds (Ov000_ProbeSaveMedia), re-locks via
 * CARD_UnlockBackup, runs Ov000_SetupWorkArea(1), and returns the sampled 0/1 flag. */

extern unsigned short data_0204be10;
extern void CARD_LockBackup(int deviceId);
extern int  Ov000_ProbeSaveMedia(void);
extern void CARD_UnlockBackup(int deviceId);
extern void Ov000_SetupWorkArea(int);

int Ov000_BackupAccessGate(void) {
    int flag;
    CARD_LockBackup(data_0204be10);
    flag = Ov000_ProbeSaveMedia() != 0;
    CARD_UnlockBackup(data_0204be10);
    Ov000_SetupWorkArea(1);
    return flag;
}
