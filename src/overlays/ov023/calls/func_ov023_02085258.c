/* func_ov023_02085258 -- ov023 scene exit. Kind 0x10 is the quiet path: run the teardown and
 * report 0. Anything else reports 1, and additionally fires the 0xe cue when the global mode
 * (func_02020a9c) is 4. */
extern void func_ov023_02084d64(void);
extern void func_02023560(int a);
extern int func_02020a9c(void);
extern void func_020056b4(int a, int b, int c);

void func_ov023_02085258(int kind) {
    if (kind == 0x10) {
        func_ov023_02084d64();
        func_02023560(0);
        return;
    }
    if (func_02020a9c() == 4) {
        func_020056b4(0xe, 4, 1);
    }
    func_02023560(1);
}
