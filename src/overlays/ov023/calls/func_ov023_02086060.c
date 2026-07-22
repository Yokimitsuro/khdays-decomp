/* func_ov023_02086060 -- script VM command: set a slot's two-word pair and its mode.
 * The pair comes from operands 2 and 3; the mode is 0 unless the fourth operand's tag is 1, in
 * which case it is read as an operand too. Always reports 1 (finished). */
extern int func_02021980(int vm, void *op);
extern int func_02021994(int vm, void *op);
extern void func_ov023_02083b7c(int idx, int *src);
extern void func_ov023_02083b94(int idx, int v);

int func_ov023_02086060(int vm, char *op) {
    int pair[2];
    int idx;
    int mode;
    idx = func_02021980(vm, op);
    mode = 0;
    pair[0] = func_02021994(vm, op + 8);
    pair[1] = func_02021994(vm, op + 0x10);
    if (*(short *)(op + 0x18) == 1) {
        mode = func_02021980(vm, op + 0x18);
    }
    func_ov023_02083b7c(idx, pair);
    func_ov023_02083b94(idx, mode);
    return 1;
}
