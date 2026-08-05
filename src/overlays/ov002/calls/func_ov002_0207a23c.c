/*
 * func_ov002_0207a23c - look up a mapped value for a key among the active objects (ARM).
 *
 * Iterates the param_1[0x50] objects (fetched one at a time by func_ov002_02076a80). For the first
 * active object (flag bit 0 at +0x12 set) whose key byte at +0x1b9 equals param_2, returns its
 * mapped value byte at +0x1ba; returns -1 if none match. The object count is re-read each iteration
 * because the per-object fetch call may change it.
 */
extern int func_ov002_02076a80(int a, int b);

int func_ov002_0207a23c(int param_1, int param_2)
{
    int i;
    for (i = 0; i < *(unsigned short *)(param_1 + 0x50); i++) {
        int entry = func_ov002_02076a80(param_1, i);
        if ((*(unsigned short *)(entry + 0x12) & 1) &&
            *(signed char *)(entry + 0x1b9) == param_2) {
            return *(signed char *)(entry + 0x1ba);
        }
    }
    return -1;
}
