/* The early path returns `result`, not the literal 0 it holds: returning the variable
 * keeps it live in a callee-saved register across the call (the ROM keeps it in r4 and
 * ends with `mov r0,r4`). `return 0;` there lets mwcc fold it away, 4 B short. */
extern int func_02030694(void);
int func_ov022_02090308(unsigned short *arg0) {
    int result = 0;
    if (func_02030694() == 0) return result;
    if ((*arg0 & 0x100) != 0) result = 1;
    return result;
}
