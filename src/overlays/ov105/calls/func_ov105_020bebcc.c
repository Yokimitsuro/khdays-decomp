extern int func_ov105_020bdd98(void *handler);
extern void func_ov105_020be4ac(int id);
extern void func_ov105_020bebf4(int req);
/* Pump the sub-state with its handler; unless it reports 2 (still running), publish the result
 * and report done. */
int func_ov105_020bebcc(void) {
    int r = func_ov105_020bdd98(&func_ov105_020bebf4);
    if (r != 2) {
        func_ov105_020be4ac(r);
        return 0;
    }
    return 1;
}
