/* Query a status word; if it reports idle (0), the object mode at +0x10 is 1 and
 * the flag at +0x19b4 is clear, advance the object via func_ov008_02064670. */
extern void func_ov008_02055dcc(void *out);
extern void func_ov008_02064670(int obj);

void func_ov008_02066ac8(int param_1) {
    char local[8];
    func_ov008_02055dcc(local);
    if (*(unsigned short *)(local + 4) == 0
        && *(int *)(param_1 + 0x10) == 1
        && *(int *)(param_1 + 0x19b4) == 0) {
        func_ov008_02064670(param_1);
    }
}
