/* Registers a sequence, stashes the handle at +0xc of the player block and hands the
 * translated handle to func_0202a208.
 *
 * The handle must be read BACK out of +0xc for the func_0201f634 call rather than kept in
 * a local: bound to a local, mwcc defers the `mov r2,r0` until after the other three
 * argument moves. */
extern int SND_RegisterSeq(int c, int d);
extern int func_0201f634(int h, int flag);
extern void func_0202a208(int a, int b, int c, int d);

int func_0202a388(int a, int b, int c, int d) {
    *(int *)(a + 0xc) = SND_RegisterSeq(c, d);
    func_0202a208(a, b, func_0201f634(*(int *)(a + 0xc), 1), d);
    return 1;
}
