#pragma thumb on
/* func_ov000_02054bac -- Scene 1 (boot/logo) save-system init + sub-mode probe, ov000.
 * THUMB. Runs once (guarded by the data_0204be14 work-buffer handle): grabs an OS
 * lock id (fatal on error), allocates the 0x2018-byte save work buffer from the boot
 * arena (data_0204c024), unlocks the CARD backup, then probes the save state to pick
 * the boot sub-mode returned to the scene ctor: 3 if func_ov000_02054904 says "fresh",
 * 5 if func_ov000_02054ac8 says "recover", else 0. Re-locks and returns the mode. */

extern void          *data_0204be14;
extern unsigned short  data_0204be10;
extern void          *data_0204c024;
extern int   OS_GetLockID(void);
extern void  OS_Terminate(void);
extern void *func_020236f8(int size, int align, void *heap);
extern void  CARD_UnlockBackup(int deviceId);
extern int   func_ov000_02054904(void);
extern int   func_ov000_02054ac8(void);
extern void  func_0200e164(int deviceId);
extern void  func_ov000_02054c50(int);

int func_ov000_02054bac(void) {
    int mode = 0;
    if (data_0204be14 != 0) {
        return 1;
    }
    data_0204be10 = OS_GetLockID();
    if (data_0204be10 == -3) {
        OS_Terminate();
    }
    data_0204be14 = func_020236f8(0x2018, 0x20, data_0204c024);
    CARD_UnlockBackup(data_0204be10);
    if (func_ov000_02054904() == 0) {
        mode = 3;
    } else if (func_ov000_02054ac8() == 0) {
        mode = 5;
    }
    func_0200e164(data_0204be10);
    func_ov000_02054c50(1);
    return mode;
}
