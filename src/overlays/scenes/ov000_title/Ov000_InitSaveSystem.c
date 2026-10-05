#pragma thumb on
/* Ov000_InitSaveSystem -- Scene 1 (boot/logo) save-system init + sub-mode probe, ov000.
 * THUMB. Runs once (guarded by the data_0204be14 work-buffer handle): grabs an OS
 * lock id (fatal on error), allocates the 0x2018-byte save work buffer from the boot
 * arena (data_0204c024), unlocks the CARD backup, then probes the save state to pick
 * the boot sub-mode returned to the scene ctor: 3 if Ov000_IdentifyBackup says "fresh",
 * 5 if Ov000_VerifySaveSignature says "recover", else 0. Re-locks and returns the mode. */

extern void          *data_0204be14;
extern unsigned short  data_0204be10;
extern void          *data_0204c024;
extern int   OS_GetLockID(void);
extern void  OS_Terminate(void);
extern void *ExpHeap_AllocOrDefault(int size, int align, void *heap);
extern void  CARD_LockBackup(int deviceId);
extern int   Ov000_IdentifyBackup(void);
extern int   Ov000_VerifySaveSignature(void);
extern void  CARD_UnlockBackup(int deviceId);
extern void  Ov000_SetupWorkArea(int);

int Ov000_InitSaveSystem(void) {
    int mode = 0;
    if (data_0204be14 != 0) {
        return 1;
    }
    data_0204be10 = OS_GetLockID();
    if (data_0204be10 == -3) {
        OS_Terminate();
    }
    data_0204be14 = ExpHeap_AllocOrDefault(0x2018, 0x20, data_0204c024);
    CARD_LockBackup(data_0204be10);
    if (Ov000_IdentifyBackup() == 0) {
        mode = 3;
    } else if (Ov000_VerifySaveSignature() == 0) {
        mode = 5;
    }
    CARD_UnlockBackup(data_0204be10);
    Ov000_SetupWorkArea(1);
    return mode;
}
