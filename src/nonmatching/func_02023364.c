/* NONMATCHING — register-reuse tie (one register differs, everything else identical).
 *
 * The whole body matches in opcode/operand/order EXCEPT which register carries the
 * `state` value: the ROM reuses r3 (the counter's now-dead register from the threshold
 * check) for the state read+update and re-derives the store address as [base+0xb0, idx],
 * while every mwcc build we have allocates a fresh r5 and folds the store address into a
 * pointer. From the state read (offset 0x1a) the split is purely r3-vs-r5 + fold-vs-index.
 * Swept 27 builds x 5 opts (THUMB); none reuses r3. Blob keeps the build byte-exact.
 *
 * Per-frame tick for sub-object param_1's swing counter: increment its counter (slot at
 * base+0xac, 8-byte stride where base = data_0204be08->[4]); once it reaches 16, flip the
 * paired state field (+0xb0) between 1 and 2, reset the counter, and kick the transform
 * update (func_02023400) with the new state. Always finalises via func_02023448. */
#pragma thumb on
extern void func_02023400(int a, int b, int c);
extern void func_02023448(int a);
extern char data_0204be08[];
void func_02023364(int param_1) {
    int idx = param_1 * 8;
    int base = *(int *)(data_0204be08 + 4);
    int cbase = base + 0xac;
    *(int *)(cbase + idx) = *(int *)(cbase + idx) + 1;
    if (*(int *)(cbase + idx) >= 0x10) {
        int state;
        if (*(int *)(base + idx + 0xb0) == 1) state = 2;
        else state = 1;
        *(int *)(base + 0xb0 + idx) = state;
        *(int *)(cbase + idx) = 0;
        func_02023400(base + 0xc, param_1, *(int *)(base + 0xb0 + idx));
    }
    func_02023448(base + 0xc);
}
