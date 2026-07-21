extern int func_ov105_020bdc6c(void *handler);
extern void func_ov105_020be4ac(int id);
extern void func_ov105_020be8d8(int req);
/* Pump the sub-state with its handler; unless it reports 2 (still running), publish the result
 * and report done. */
int func_ov105_020be8b0(void) {
    int r = func_ov105_020bdc6c(&func_ov105_020be8d8);
    if (r != 2) {
        func_ov105_020be4ac(r);
        return 0;
    }
    return 1;
}
