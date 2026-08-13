/* Tear the HUD down if the panel is in state 4, and report whether it happened.
 *
 * With no context there is nothing to dismiss, so the caller's own value comes straight back out.
 * Otherwise the entry named by the key at 0x69c is selected, and a panel sitting in state 4 is
 * torn down with the cancel sound before the key at 0x6a0 is selected instead.
 *
 * Three details carry the original codegen. The caller's value is returned by an early return
 * rather than through the result variable, so the original never has to save r0. The state test
 * is written not-equal, leaving the dismissal arm out of line. And the result is initialised to
 * one where it is declared, ahead of the null check, with only the not-equal arm clearing it.
 */

typedef unsigned int u32;

extern char *data_ov002_0207f624;
extern void func_ov002_020539f4(int key);
extern long long func_ov002_02053b28(int a, int b, int c, int d, int e);
extern void func_ov002_0205eca0(long long value);
extern void func_02033b78(int a, int b);

u32 func_ov002_0205f3a4(u32 fallback) {
    u32 result = 1;
    char *ctx = data_ov002_0207f624;

    if (ctx == 0) {
        return fallback;
    }
    func_ov002_020539f4(*(int *)(ctx + 0x69c));
    if (*(int *)ctx != 4) {
        result = 0;
    } else {
        func_ov002_0205eca0(func_ov002_02053b28(9, 0, 0, 0x20, 0x18));
        func_02033b78(0, 10);
    }
    func_ov002_020539f4(*(int *)(ctx + 0x6a0));
    return result;
}
