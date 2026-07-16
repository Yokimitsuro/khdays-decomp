/* func_ov025_020a4f4c -- run the two-pass update and report whether either pass did anything.
 * The first pass always runs, for the kind func_ov025_02084cb4 names; only if it reported work
 * does the second pass run, for func_ov025_02084c9c's kind. Reports true if either did.
 * func_ov025_020a4e74 is primed with func_ov025_02084c84's kind first. */
extern int func_ov025_02084c84(void);
extern void func_ov025_020a4e74(int obj, int kind);
extern int func_ov025_02084cb4(void);
extern int func_ov025_020a4eb8(int obj, int a, int b, int kind);
extern int func_ov025_02084c9c(void);

int func_ov025_020a4f4c(int obj, int a, int b) {
    int first;
    int second;

    second = 0;
    func_ov025_020a4e74(obj, func_ov025_02084c84());
    first = func_ov025_020a4eb8(obj, a, b, func_ov025_02084cb4());
    if (first != 0) {
        second = func_ov025_020a4eb8(obj, a, b, func_ov025_02084c9c());
    }
    return first != 0 || second != 0;
}
