/* NONMATCHING: block-layout tie — the ROM branches to a separate `ldr r4,=handler` block (with a
 * redundant `b` back), mwcc fuses it into a predicated `ldreq r4,=handler` (56B vs 64B). Twin of
 * func_ov006_0204ed64. "Our compiler is smarter" class. */
/* func_ov008_0207ab10 -- pick the ov008 idle handler by scene state: state 1 (loading) returns
 * func_ov008_0207aac8; states 0 and 3 return none; any other state kicks func_ov105_020bf928
 * and returns none. */
extern int  func_02001030(void);   /* Game_PollSceneAlive */
extern void func_ov105_020bf928(void);
extern void func_ov008_0207aac8(void);

int func_ov008_0207ab10(void) {
    int result = 0;
    int state = func_02001030();
    if (state != 0) {
        if (state == 1) {
            result = (int)func_ov008_0207aac8;
        } else if (state != 3) {
            func_ov105_020bf928();
        }
    }
    return result;
}
