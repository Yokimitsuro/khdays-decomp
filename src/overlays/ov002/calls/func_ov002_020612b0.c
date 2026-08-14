/* Put the title widget back to its starting state.
 *
 * The widget lives 0x132c into the scene object; it is placed from a language-dependent resource
 * path with an empty three-word box, given its follow-up pass, and then the four words at 0x1464
 * are cleared.
 *
 * The box is written as an initialiser rather than three assignments on purpose: that is what
 * makes the compiler take its address into a register and store through it, where separate
 * assignments give stack-relative stores instead.
 */

extern char *data_ov002_0207f628;
extern char data_ov002_0207ebc4[];
extern char *func_02024e6c(char *name);
extern void func_ov002_0205f5e0(char *widget, char *path, int *box, int flags, int mode);
extern void func_ov002_02061290(char *widget);

void func_ov002_020612b0(void) {
    char *ctx = data_ov002_0207f628;
    int box[3] = { 0, 0, 0 };
    int i;
    func_ov002_0205f5e0(ctx + 0x132c, func_02024e6c(data_ov002_0207ebc4), box, 0x20000, 5);
    func_ov002_02061290(ctx + 0x132c);
    i = 0;
    do {
        i++;
        *(int *)(ctx + 0x1464) = 0;
        ctx += 4;
    } while (i < 4);
}
