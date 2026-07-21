/* Draw a text/box element, optionally preceded by a drop-shadow pass offset by (+1,+1,-1). Both
 * passes use flags 0x821. */
extern void func_020301c8(int p1, int p2, int p3, int p4, int flags, int p6);

void func_ov025_020a276c(int p1, int p2, int p3, int p4, int bShadow, int p6) {
    if (bShadow != 0) {
        func_020301c8(p1, p2 + 1, p3 + 1, p4 - 1, 0x821, p6);
    }
    func_020301c8(p1, p2, p3, p4, 0x821, p6);
}
