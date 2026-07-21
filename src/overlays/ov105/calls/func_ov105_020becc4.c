extern void func_ov105_020be4ac(unsigned int id);
extern void func_ov105_020be49c(int state);
extern int func_ov105_020becfc(void);
/* If the request carries a target id, apply it and go to state 9; otherwise try the fallback and
 * only fall back to state 9 when it declines. */
void func_ov105_020becc4(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        func_ov105_020be4ac(*(unsigned short *)(req + 2));
        func_ov105_020be49c(9);
        return;
    }
    if (func_ov105_020becfc() != 0) {
        return;
    }
    func_ov105_020be49c(9);
}
