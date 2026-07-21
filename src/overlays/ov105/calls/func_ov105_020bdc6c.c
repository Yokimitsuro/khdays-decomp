extern int func_ov105_020bd0a0(int a, int b);
extern void func_ov105_020bcea0(int slot, int arg);
extern int func_ov105_020bcf10(int slot, int flag);
/* Same transition shape as 020bda94, driving stage 7 into slot 9. */
int func_ov105_020bdc6c(int arg) {
    int r = func_ov105_020bd0a0(1, 7);
    if (r != 0) {
        return r;
    }
    func_ov105_020bcea0(9, arg);
    r = func_ov105_020bcf10(9, 0);
    if (r == 0) {
        r = 2;
    }
    return r;
}
