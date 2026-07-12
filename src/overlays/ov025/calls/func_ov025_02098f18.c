/* Query a status word; if it reports idle (0), the object mode at +0x10 is 1 and
 * the flag at +0x19b4 is clear, advance the object via func_ov025_02096b9c. */
extern void func_ov025_020899dc(void *out);
extern void func_ov025_02096b9c(int obj);

void func_ov025_02098f18(int param_1) {
    char local[8];
    func_ov025_020899dc(local);
    if (*(unsigned short *)(local + 4) == 0
        && *(int *)(param_1 + 0x10) == 1
        && *(int *)(param_1 + 0x19b4) == 0) {
        func_ov025_02096b9c(param_1);
    }
}
