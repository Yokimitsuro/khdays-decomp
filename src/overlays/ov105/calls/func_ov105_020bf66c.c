extern void func_ov105_020be49c(int state);
extern int OS_UnlockByWord_0x020bd9ec(int handle, void *fn, int a);
extern void func_ov105_020be4ac(void);
extern void func_ov105_020bf6b4(void);
extern char *data_ov105_020c04c0;

/* Runs the step-3 sub-task on the backend's second handle; 1 while it is still going, 0 once it
 * has finished and the task has moved on to step 0xa. */
int func_ov105_020bf66c(void) {
    func_ov105_020be49c(3);
    if (OS_UnlockByWord_0x020bd9ec(*(int *)((char *)&data_ov105_020c04c0 + 0x4c),
                                   (void *)&func_ov105_020bf6b4, 2) == 2) {
        return 1;
    }
    func_ov105_020be4ac();
    func_ov105_020be49c(0xa);
    return 0;
}
