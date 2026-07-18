/* Look up the object for param_1; return 0 only when its bit 2 flag at +0x28 is
 * set and the word at +0x1f0 is zero; otherwise 1. */
extern int func_ov025_02084b14(int arg);

struct flags_0207890c { unsigned int pad : 2; unsigned int active : 1; };

int func_ov025_020afd18(int param_1) {
    int obj = func_ov025_02084b14(param_1);
    return !((struct flags_0207890c *)(obj + 0x28))->active
        || *(int *)(obj + 0x1f0) != 0;
}
