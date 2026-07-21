extern void func_ov105_020be49c(int state);
extern void func_ov105_020be4ac(unsigned int id);
extern void func_ov105_020be43c(void);
/* If the request carries a target id, go to state 9 and apply it; otherwise reset and return to
 * state 1. */
void func_ov105_020bf038(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        func_ov105_020be49c(9);
        func_ov105_020be4ac(*(unsigned short *)(req + 2));
        return;
    }
    func_ov105_020be43c();
    func_ov105_020be49c(1);
}
