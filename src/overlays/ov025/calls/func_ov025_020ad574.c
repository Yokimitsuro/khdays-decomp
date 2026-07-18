/* ⚠ The third test is a DUPLICATE of the second and is dead -- but it is in the original.
 * It compiles to the `popne {r3,pc}` at +0x34, which is reached only via the `beq` above
 * it, so it can never fire; mwcc reuses the flags rather than re-comparing. Dropping it
 * compiles 4 B short. Do not "simplify" it away. */
extern void func_ov025_020ac4d8(int obj, int arg);
extern void func_ov025_020aa0a4(int obj, int col);
extern void func_02033b78(int a, int b);

void func_ov025_020ad574(int param_1) {
    if (*(int *)(param_1 + 0x158) != 0) {
        return;
    }
    if (*(int *)(param_1 + 0x180) != 0) {
        func_ov025_020ac4d8(param_1, *(int *)(param_1 + 0x184) == 0);
        return;
    }
    if (*(int *)(param_1 + 0x180) != 0) {
        return;
    }
    {
        int page = *(int *)(param_1 + 4) + 2;
        func_ov025_020aa0a4(param_1, page % 3);
        func_02033b78(0, 0);
    }
}
