/* func_ov025_0208bda0 -- ov025 "back": close the sub-panel (obj+0x94) if one is open, else the
 * popup (obj+0x5c0) if one is open, else leave the menu entirely (func_ov002_0206d970 + clear the
 * selection). Always fires UI event 3. */
extern void func_ov025_0208b274(int obj, int arg);
extern void func_ov025_0208ad30(int obj, int arg);
extern void func_ov002_0206d970(int arg);
extern void func_ov025_02084798(int a, int b);
extern void func_02033b78(int a, int b);

void func_ov025_0208bda0(int param_1) {
    if (*(int *)(param_1 + 0x94) != 0) {
        func_ov025_0208b274(param_1, 0);
    } else if (*(int *)(param_1 + 0x5c0) != 0) {
        func_ov025_0208ad30(param_1, 0);
    } else {
        func_ov002_0206d970(0);
        func_ov025_02084798(-1, -1);
    }
    func_02033b78(0, 3);
}
