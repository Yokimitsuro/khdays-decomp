/* func_ov023_0208564c -- reset the script VM's 0x100-byte register block and re-arm the command.
 * The block starts at +0x4a4 of the VM state (+0x128 of the caller's object). Clearing it,
 * running func_ov023_0208557c and re-arming with func_020219b4 always reports 0 (command not
 * finished). */
extern void INITi_CpuClear32_0x01ff86fc(int value, void *dst, int size);
extern void func_ov023_0208557c(int a, int b);
extern void func_020219b4(int a, int b);

int func_ov023_0208564c(int a, int b) {
    INITi_CpuClear32_0x01ff86fc(0, (void *)(*(int *)(a + 0x128) + 0x4a4), 0x100);
    func_ov023_0208557c(a, b);
    func_020219b4(a, b);
    return 0;
}
