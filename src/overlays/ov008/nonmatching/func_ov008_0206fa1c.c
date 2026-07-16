/* NONMATCHING: -8B CSE tie -- the ROM holds the node tutorial id in r4 and recomputes id+0x3bd5
 * (add #0xd5; add #0x3b00) before each of the two flag calls; our mwcc caches the sum. */
/* func_ov008_0206fa1c -- fire the "first time on this mission node" tutorial once, ov008.
 * Skips (returns false) while input is locked (func_ov008_02050ff8). Otherwise resolves the
 * current node's tutorial flag id (from the 9-bit selector at event 0 through the ba30/ba1c
 * lookups, + base 0x3bd5) and, if that story flag is still clear, posts it and returns true. */
extern int func_ov008_02050ff8(void);
extern int func_020235d0(int event, int bits);
extern int func_ov008_0205ba30(unsigned int a);
extern unsigned short func_ov008_0205ba1c(unsigned int a);
extern int func_02023588(int flag);
extern void func_020235a8(int flag);

int func_ov008_0206fa1c(void) {
    unsigned int v;
    unsigned short id;
    int result;
    if (func_ov008_02050ff8() != 0) {
        return 0;
    }
    v = func_020235d0(0, 9);
    v = func_ov008_0205ba30(v & 0xffff);
    id = func_ov008_0205ba1c(v & 0xffff);
    result = 0;
    if (func_02023588(id + 0x3bd5) == 0) {
        func_020235a8(id + 0x3bd5);
        result = 1;
    }
    return result;
}
