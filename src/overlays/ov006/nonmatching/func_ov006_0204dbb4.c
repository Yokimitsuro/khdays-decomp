/* NONMATCHING: semantics correct; block-layout tie -- the ROM places the state==1 (020bf9c0)
 * block out-of-line and emits an extra `b` to the 020bf928 tail (80B); our mwcc inlines the
 * then-block and falls through to 020bf928 (76B). No C ordering reproduces the placement. */
/* func_ov006_0204dbb4 -- pump the scene transition while the Mission Mode is active.
 * On scene state 1 (loading): once func_ov105_020bf9c0 signals ready, clear the Mission Mode busy field
 * (ctx+0x49c). On states other than 0/1/3, kick func_ov105_020bf928. States 0 and 3 do nothing. */
extern int  func_02001030(void);            /* Game_PollSceneAlive */
extern int  func_ov105_020bf9c0(void);
extern void func_ov105_020bf928(void);
extern int  data_ov006_020565e4;   /* -> Mission Mode-screen context */

void func_ov006_0204dbb4(void) {
    int state = func_02001030();
    if (state == 0) {
        return;
    }
    if (state != 1) {
        if (state == 3) {
            return;
        }
        func_ov105_020bf928();
        return;
    }
    if (func_ov105_020bf9c0() == 0) {
        return;
    }
    *(int *)(data_ov006_020565e4 + 0x49c) = 0;
}
