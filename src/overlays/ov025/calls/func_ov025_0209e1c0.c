extern int func_ov025_02084afc(void);
extern void func_020301c8(int ctx, int x, int y, int w, unsigned int style, int text);
/* Draw the string, first offset by one pixel as a drop shadow when requested. */
void func_ov025_0209e1c0(int text, int x, int y, int w, unsigned int style, int shadow) {
    int page = func_ov025_02084afc();
    if (shadow != 0) {
        func_020301c8(page + 0x84, x + 1, y + 1, w - 1, style, text);
    }
    func_020301c8(page + 0x84, x, y, w, style, text);
}
