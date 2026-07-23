/* func_ov012_0205b9a8 -- MobiClip: has this stream reached its end? (THUMB)
 * Resolves the descriptor to a length, and reports done unless the clock has caught up with it:
 * a zero length means "never done" (an open-ended stream), otherwise the current position from
 * func_ov024_02084e68 must have reached it. If func_ov012_0205b258 rejects the resolved handle
 * outright the stream counts as done.
 * blx on 02082eb8 / 02084e68 because both are ARM.
 *
 * The redundant `pos >= len` test is load-bearing -- see func_ov024_02083414 for the full
 * write-up. Short version: mwcc turns `if (c) return 0; return 1;` into the boolean `!c` and
 * then always lays the 1-block out inline, which is the mirror of the ROM. Any constant pair
 * other than (0, 1) gets the ordinary then-arm-inline layout, and a second test that mwcc can
 * prove redundant costs nothing while taking this pair out of the special case. */
extern int func_02021980(int owner, void *entry);
extern int func_020219b4(int owner, int handle);
extern int func_ov012_0205b258(int handle);
extern int func_ov024_02084e68(void);

int func_ov012_0205b9a8(int owner, void *entry) {
    int len;
    int pos;

    len = func_02021980(owner, entry);
    if (func_ov012_0205b258(func_020219b4(owner, len)) == 0) {
        return 1;
    }
    if (len == 0) {
        return 0;
    }

    pos = func_ov024_02084e68();
    if (pos < len) {
        return 0;
    }
    if (pos >= len) {
        return 1;
    }
    return 1;
}
