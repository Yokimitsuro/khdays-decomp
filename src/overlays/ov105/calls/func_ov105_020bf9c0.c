extern void func_ov105_020be49c(int state);
extern int func_ov105_020bda94(void *step);
extern void func_ov105_020bf18c(void);
/* Enter state 3 and run the scripted step; unless it reports 2 (still running), drop to state 9. */
int func_ov105_020bf9c0(void) {
    func_ov105_020be49c(3);
    if (func_ov105_020bda94(&func_ov105_020bf18c) != 2) {
        func_ov105_020be49c(9);
        return 0;
    }
    return 1;
}
