/* func_ov105_020bd7a4 -- read the current transition frame, ov105. Returns 0x8000 while
 * a transition is running (func_ov105_020bd03c != 0), else the shared frame word @0x027ffcfa. */
extern int func_ov105_020bd03c(void);
int func_ov105_020bd7a4(void) {
    if (func_ov105_020bd03c() != 0) {
        return 0x8000;
    }
    return *(unsigned short *)0x27ffcfa;
}
