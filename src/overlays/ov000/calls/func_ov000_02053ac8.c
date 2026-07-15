/* func_ov000_02053ac8 -- dispatch a logo action by selector, ov000. Routes arg to
 * one of three handlers (0/1/2); ignores any other selector. */
extern void func_ov000_02053740(int arg);
extern void func_ov000_020537fc(int arg);
extern void func_ov000_02053928(int arg);
void func_ov000_02053ac8(int sel, int arg) {
    switch (sel) {
    case 0: func_ov000_02053740(arg); break;
    case 1: func_ov000_020537fc(arg); break;
    case 2: func_ov000_02053928(arg); break;
    }
}
