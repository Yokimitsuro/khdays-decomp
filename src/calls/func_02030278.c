/* func_02030278 -- Text_DrawWithShadow (116 B, 2 relocs).
 * Draws a UTF-16 text buffer with an optional drop shadow. When `shadow` is set it first draws the
 * buffer offset by (+1,+1) one depth behind (func_020301c8 with style 0x209), then draws the main
 * copy at (x, y, depth). Used by the menu row renderer (func_ov008_0206c36c) for labels. */
extern void func_020301c8(int dctx, int x, int y, int mode, int style, void *buf);

void func_02030278(int dctx, int x, int y, int depth, void *buf, int shadow)
{
    if (shadow != 0)
        func_020301c8(dctx, x + 1, y + 1, depth - 1, 0x209, buf);
    func_020301c8(dctx, x, y, depth, 0x209, buf);
}
