/* NONMATCHING: semantics correct; the ROM copies the func_0206fce0 result into r1 (`mov r1,r0`)
 * and works from there, mwcc uses r0 directly and elides the copy (100B vs 104B). "Our compiler
 * is smarter" class, same as 0205b720 / 0207350c. */
/* func_ov008_02073df0 -- update the hovered mission row while dragging.
 * Requires the panel fully idle (obj[0x1a], obj[0x13e], obj[0xc] all clear), a page transition
 * running (func_ov008_02051028) and a mode other than 7. Re-resolves the row
 * (func_ov008_0206fce0(obj,1)); if it changed, stores it at obj+0x54 and refreshes. */
extern int  func_ov008_02051028(void);
extern int  func_ov008_0205b7b4(void);
extern unsigned int func_ov008_0206fce0(int obj, int arg);
extern void func_ov008_02072d9c(unsigned int *obj);

void func_ov008_02073df0(unsigned int *param_1) {
    unsigned int row;
    if (param_1[0x1a] != 0 || param_1[0x13e] != 0 || param_1[0xc] != 0) {
        return;
    }
    if (func_ov008_02051028() == 0) {
        return;
    }
    if (func_ov008_0205b7b4() == 7) {
        return;
    }
    row = func_ov008_0206fce0((int)param_1, 1);
    if (row != *(unsigned char *)((char *)param_1 + 0x54)) {
        *(unsigned char *)((char *)param_1 + 0x54) = (unsigned char)row;
        func_ov008_02072d9c(param_1);
    }
}
