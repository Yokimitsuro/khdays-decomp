/* func_ov024_020833b8 -- MobiClip: resolve two descriptor entries and open the pair (THUMB).
 * Entries are 8 bytes apart, same layout func_ov024_02083368 walks. Both handles go to
 * func_ov024_02082e04 together; the constant 6 is the resulting stream state.
 * blx because 02082e04 is ARM. */
extern int func_02021980(int owner, char *entry);
extern void func_ov024_02082e04(int a, int b);

int func_ov024_020833b8(int owner, char *desc) {
    int a;
    int b;

    a = func_02021980(owner, desc);
    b = func_02021980(owner, desc + 8);
    func_ov024_02082e04(a, b);
    return 6;
}
