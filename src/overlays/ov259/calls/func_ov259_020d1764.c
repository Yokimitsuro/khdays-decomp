/* Swap which of the ov259 rig's two shells is shown: `open` scales the +0x388 shell to 1.0 and
 * hides the +0x384 one, otherwise the reverse (0203ca9c on each transform). */
extern void func_0203ca9c(int srt, int scale);

void func_ov259_020d1764(char *self, int open)
{
    if (open) {
        func_0203ca9c(*(int *)(self + 0x388) + 4, 0x1000);
        func_0203ca9c(*(int *)(self + 0x384) + 4, 0);
    } else {
        func_0203ca9c(*(int *)(self + 0x388) + 4, 0);
        func_0203ca9c(*(int *)(self + 0x384) + 4, 0x1000);
    }
}
