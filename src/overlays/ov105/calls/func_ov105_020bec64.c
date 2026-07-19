extern void func_ov105_020be49c(int state);
extern int func_ov105_020be304(void *fn, int handle, void *arg);
extern void func_ov105_020be4ac(void);
extern void func_ov105_020becc4(void);
extern int data_ov105_020c04c0;
extern int data_ov105_020c0520;
extern int data_ov105_020c05c0;

/* Runs the step-3 sub-task through the backend's own opener; returns 1 while it is still going,
 * 0 once it has finished and the task has moved on to step 9. */
int func_ov105_020bec64(void) {
    int handle;
    func_ov105_020be49c(3);
    handle = (*(int (**)(void *, void *))((char *)&data_ov105_020c04c0 + 0x40))(
        &data_ov105_020c0520, &data_ov105_020c05c0);
    if (func_ov105_020be304((void *)&func_ov105_020becc4, handle, &data_ov105_020c0520) == 2) {
        return 1;
    }
    func_ov105_020be4ac();
    func_ov105_020be49c(9);
    return 0;
}
