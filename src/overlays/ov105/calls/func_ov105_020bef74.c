extern void func_ov105_020be4ac(unsigned int id);
extern void func_ov105_020bf928(void);
extern int func_ov105_020befa8(void);
extern void func_ov105_020be49c(int state);

/* If the request carries a target id, apply it and finish; otherwise try the fallback and only
 * go to state 9 when it declines. */
void func_ov105_020bef74(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        func_ov105_020be4ac(*(unsigned short *)(req + 2));
        func_ov105_020bf928();
        return;
    }
    if (func_ov105_020befa8() != 0) {
        return;
    }
    func_ov105_020be49c(9);
}
