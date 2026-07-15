#pragma thumb on
/* func_ov000_02054c20 -- Scene 1 (boot/logo) backup-access gate, ov000. THUMB.
 * Unlocks the save (CARD) backup for the current device id (data_0204be10),
 * samples whether a follow-up condition holds (func_ov000_02054b1c), re-locks via
 * func_0200e164, runs func_ov000_02054c50(1), and returns the sampled 0/1 flag. */

extern unsigned short data_0204be10;
extern void CARD_UnlockBackup(int deviceId);
extern int  func_ov000_02054b1c(void);
extern void func_0200e164(int deviceId);
extern void func_ov000_02054c50(int);

int func_ov000_02054c20(void) {
    int flag;
    CARD_UnlockBackup(data_0204be10);
    flag = func_ov000_02054b1c() != 0;
    func_0200e164(data_0204be10);
    func_ov000_02054c50(1);
    return flag;
}
