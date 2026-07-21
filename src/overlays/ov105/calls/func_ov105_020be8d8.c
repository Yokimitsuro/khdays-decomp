extern void func_ov105_020be4ac(unsigned int id);
extern void func_ov105_020be43c(void);
extern void func_ov105_020be49c(int state);
/* If the request carries a target id, hand it to the mode-gated setter; otherwise reset and go
 * back to state 1. */
void func_ov105_020be8d8(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        func_ov105_020be4ac(*(unsigned short *)(req + 2));
        return;
    }
    func_ov105_020be43c();
    func_ov105_020be49c(1);
}
