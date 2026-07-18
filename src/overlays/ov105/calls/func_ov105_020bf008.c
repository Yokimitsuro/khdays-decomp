/*
 * func_ov105_020bf008 -- x3 (ov105/...). Enter mode 3 and run its callback-driven step.
 * Set mode via 020be49c(3), then run 020be294(&020be880). If it reports 2 (still busy) return 1;
 * otherwise commit the result through 020be4ac(result) and return 0.
 */
extern void func_ov105_020be49c(int mode);
extern int func_ov105_020bda5c(void *cb);
extern void func_ov105_020be4ac(int result);
extern void func_ov105_020bf038(void);

int func_ov105_020bf008(void) {
    int r;

    func_ov105_020be49c(3);
    r = func_ov105_020bda5c(&func_ov105_020bf038);
    if (r == 2) {
        return 1;
    }
    func_ov105_020be4ac(r);
    return 0;
}
