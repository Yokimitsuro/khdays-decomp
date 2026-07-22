/* func_ov022_0209e4a4 -- run one battle-HUD sub-pass for a party member, unless it is suppressed.
 * Nothing happens while bit 0x10000 of the object's first word is set. Otherwise the pass only
 * runs in mode 4 (+0x26c0) and while the target's flags halfword (+0x12 of the object at +0x26d4)
 * has bit 0x200 clear; it then builds a 3-word descriptor from the row at +0x22c8 and the target's
 * own parameters (func_ov002_02076cc8) and hands it to the two draw calls. Returns 1 when it ran.
 *
 * Parked as a "single-register tie": the ROM loads the flags halfword into r1 and keeps the target
 * pointer in r0, mwcc uses r0 for the halfword. r0 stays live because it is the ARGUMENT of
 * func_ov002_02076cc8, which was declared `(void)` here and is defined with one parameter
 * (tools/audit_extern_sig.py names it). With the argument present the halfword has to go to r1 and
 * the function matches. "One register differs and both look dead" is what a dropped argument looks
 * like -- check the extern against the definition before calling it a colouring tie.
 */
extern int func_ov002_02076cc8(int obj);
extern void func_ov022_020a1118(unsigned int *a, int b, int *c, int *d, unsigned int *e);
extern void func_ov022_020a1258(int a, unsigned int *b, int c, unsigned int *d, int e);

int func_ov022_0209e4a4(unsigned int *param_1, unsigned int *param_2, unsigned int *param_3,
                        int param_4) {
    unsigned int auStack_24[3];
    int uVar2 = 0;
    if ((*param_1 & 0x10000) != 0) {
        return 0;
    }
    if (param_1[0x9b0] == 4 && (*(unsigned short *)(param_1[0x9b5] + 0x12) & 0x200) == 0) {
        int *piVar1;
        uVar2 = 1;
        piVar1 = (int *)func_ov002_02076cc8(param_1[0x9b5]);
        func_ov022_020a1118(auStack_24, (int)param_2, (int *)(param_1 + 0x9b2), piVar1, param_3);
        func_ov022_020a1258((int)param_1, param_2, param_1[0x9b5], auStack_24, 1);
    }
    return uVar2;
}
