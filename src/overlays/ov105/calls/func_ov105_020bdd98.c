extern int func_ov105_020bd0a0(int a, int b);
extern void func_ov105_020bcea0(int slot, int arg);
extern int func_ov105_020bcf10(int slot, int flag);
/* Run phase 1->2 of the transition: bail out with the first stage's code if it is busy, else
 * arm slot 2 and report its status (0 meaning "still running" is reported as 2). */
int func_ov105_020bdd98(int arg) {
    int r = func_ov105_020bd0a0(1, 5);
    if (r != 0) {
        return r;
    }
    func_ov105_020bcea0(0xb, arg);
    r = func_ov105_020bcf10(0xb, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
