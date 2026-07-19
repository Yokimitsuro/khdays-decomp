extern void func_ov105_020be49c(int state);
extern int func_ov105_020bdad4(void *fn, void *arg);
extern void func_ov105_020be4ac(void);
extern void func_ov105_020be508(void);
extern int data_ov105_020c0580;

/* Runs the step-3 sub-task; returns 1 while it is still going, 0 once it has finished and the
 * task has moved on to step 9. */
int func_ov105_020be4c8(void) {
    func_ov105_020be49c(3);
    if (func_ov105_020bdad4((void *)&func_ov105_020be508, &data_ov105_020c0580) == 2) {
        return 1;
    }
    func_ov105_020be4ac();
    func_ov105_020be49c(9);
    return 0;
}
