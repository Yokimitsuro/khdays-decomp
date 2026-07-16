/* func_ov024_02083ccc -- MobiClip: close the render pass opened by func_ov024_020835d8.
 * The open flag lives at +0x50; if it is clear there is nothing to close. */
extern void func_0202f9f8(int p);

void func_ov024_02083ccc(int p) {
    if (*(int *)(p + 0x50) == 0) {
        return;
    }
    func_0202f9f8(p);
    *(int *)(p + 0x50) = 0;
}
