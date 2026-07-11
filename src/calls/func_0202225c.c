/* Gate a deferred action for slot param_1: when param_2 (a frame budget) is 0, allow
 * only if bit 0 of the global flags (data_0204c190) is set; otherwise allow only if the
 * available thread/frame count (OS_IsThreadAvailable) is at least param_2, else enqueue
 * the fallback (func_020219b4) and deny. Returns 1 to proceed, 0 to skip. */
#pragma thumb on
extern unsigned int OS_IsThreadAvailable(void);
extern void func_020219b4(int a, unsigned int b);
extern unsigned short data_0204c190;
int func_0202225c(int param_1, unsigned int param_2) {
    if (param_2 == 0) {
        if (data_0204c190 & 1) return 1;
        return 0;
    }
    if (OS_IsThreadAvailable() < param_2) {
        func_020219b4(param_1, param_2);
        return 0;
    }
    return 1;
}
