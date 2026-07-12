/* Shut down: run cleanup 0204d358(1), terminate, return 0. */
extern void func_ov000_0204d358(int);
extern void OS_Terminate(void);
int func_ov000_0204f6c8(void) {
    func_ov000_0204d358(1);
    OS_Terminate();
    return 0;
}
