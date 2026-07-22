/* Fire the "first time on this mission node" tutorial once. Does nothing while input is locked;
 * otherwise resolves the current node's tutorial flag id through the two lookups and, if that
 * story flag is still clear, posts it and answers true.
 *
 * Parked as a CSE tie -- the original recomputes `id + 0x3bd5` (a two-instruction constant add)
 * before each of the two flag calls while mwcc caches the sum. The fix is not about the sum at
 * all: the two lookups take `unsigned short`, so the narrowing after each call belongs to the
 * CALL, and the calls chain directly into one another. Written with `& 0xffff` and intermediate
 * locals, the whole dataflow lands in the caller where mwcc is free to reuse it; nested, it
 * comes out as the original has it. */
extern int func_ov025_02084e08(void);
extern int func_020235d0(int event, int bits);
extern int func_ov025_0208dfc4(unsigned short sel);
extern int func_ov025_0208dfb0(unsigned short node);
extern int func_02023588(int flag);
extern void func_020235a8(int flag);

int func_ov025_020a4fc0(void) {
    int id;
    int result;

    if (func_ov025_02084e08() != 0) {
        return 0;
    }
    id = func_ov025_0208dfb0(func_ov025_0208dfc4(func_020235d0(0, 9)));
    result = 0;
    if (func_02023588(id + 0x3bd5) == 0) {
        func_020235a8(id + 0x3bd5);
        result = 1;
    }
    return result;
}
