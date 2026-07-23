/* func_ov008_0207b8a8 -- tick the key-sharing shutdown timer. Does nothing while the session
 * handle at +4 is null. Otherwise counts the halfword at (session + 0x400) + 0xf2 down by one per
 * call and returns; when it reaches zero, ends key sharing for that handle and clears the handle.
 *
 * This was filed as a "PROVEN TIE (register coloring only)" -- an r0/r1 swap with everything else
 * identical. It was two real source bugs, and the second one is the interesting half.
 *
 * 1. A DROPPED ARGUMENT. WM_EndKeySharing_0x02023ad0 takes the handle; the old source declared it
 *    `(void)` and called it with none. The ROM's `bl` is reached with r0 still holding the value
 *    loaded by `ldr r0,[r1,#4]` at the top -- that is the argument, not a leftover. Passing it
 *    keeps the handle live in r0 across the whole body, which is precisely what forces the base
 *    pointer into r1 and produced the "swap".
 *
 * 2. THE BASE MUST BE ADVANCED IN PLACE. Written as one expression,
 *    `base = (char *)(*(int *)&data + 0x400);` mwcc loads the pointer into r1 and lands the sum in
 *    a fresh r2, then puts the counter in r1 -- the last two registers stay swapped. Split into
 *    `base = (char *)*(int *)&data;` then `base += 0x400;` and mwcc updates r1 in place
 *    (`ldr r1,[r1]` / `add r1,r1,#0x400`), leaving r2 for the counter exactly as the ROM does.
 *    Same total instructions either way; only the register choice differs.
 */
extern int data_ov008_02090f24;
extern int WM_EndKeySharing_0x02023ad0(int handle);

void func_ov008_0207b8a8(void) {
    char *base;
    unsigned short c;
    int handle = *(int *)((char *)&data_ov008_02090f24 + 4);

    if (handle == 0) {
        return;
    }
    base = (char *)*(int *)&data_ov008_02090f24;
    base += 0x400;

    c = *(unsigned short *)(base + 0xf2);
    if (c != 0) {
        *(unsigned short *)(base + 0xf2) = c - 1;
        return;
    }
    WM_EndKeySharing_0x02023ad0(handle);
    *(int *)((char *)&data_ov008_02090f24 + 4) = 0;
}
