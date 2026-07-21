extern int func_ov105_020bd058(void);
extern void func_ov105_020bcea0(int slot, int arg);
extern int func_ov105_020bcf10(int slot, int flag);
/* Same transition shape as 020bda94, with an argument-less first stage, into slot 1. */
int func_ov105_020bda5c(int arg) {
    int r = func_ov105_020bd058();
    if (r != 0) {
        return r;
    }
    func_ov105_020bcea0(1, arg);
    r = func_ov105_020bcf10(1, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
