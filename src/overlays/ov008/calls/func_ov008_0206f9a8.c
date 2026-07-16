/* func_ov008_0206f9a8 -- run the two-pass update and report whether either pass did anything.
 * The first pass always runs, for the kind func_ov008_02050ea4 names; only if it reported work
 * does the second pass run, for func_ov008_02050e8c's kind. Reports true if either did.
 * func_ov008_0206f8d0 is primed with func_ov008_02050e74's kind first. */
extern int func_ov008_02050e74(void);
extern void func_ov008_0206f8d0(int obj, int kind);
extern int func_ov008_02050ea4(void);
extern int func_ov008_0206f914(int obj, int a, int b, int kind);
extern int func_ov008_02050e8c(void);

int func_ov008_0206f9a8(int obj, int a, int b) {
    int first;
    int second;

    second = 0;
    func_ov008_0206f8d0(obj, func_ov008_02050e74());
    first = func_ov008_0206f914(obj, a, b, func_ov008_02050ea4());
    if (first != 0) {
        second = func_ov008_0206f914(obj, a, b, func_ov008_02050e8c());
    }
    return first != 0 || second != 0;
}
