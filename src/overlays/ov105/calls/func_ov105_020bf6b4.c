extern void func_ov105_020be4ac(void);
extern void func_ov105_020be49c(int state);
extern int func_ov105_020bd558(void *fn);
extern void func_ov105_020bf64c(void);

/* Step handler: leaves for state 0xa when the request word is set or the sub-task is still
 * running, otherwise falls back to state 1. */
void func_ov105_020bf6b4(unsigned short *req) {
    if (req[1] != 0) {
        func_ov105_020be4ac();
        func_ov105_020be49c(0xa);
        return;
    }
    if (func_ov105_020bd558((void *)&func_ov105_020bf64c) != 0) {
        func_ov105_020be4ac();
        func_ov105_020be49c(0xa);
        return;
    }
    func_ov105_020be49c(1);
}
