/* func_02013768 -- text line-width measure (172 B, 2 relocs).
 * Measures one line of a UTF-16 string: walks characters via the font's getNextChar callback
 * (font[1], which advances the cursor), stops at NUL or newline (0xa), and sums opts + the glyph
 * advance for each. Each char is mapped to a glyph index by func_020136d4(font, ch); an unmapped
 * char (0xffff) falls back to the font's default glyph (*(u16 *)(*font + 2)); the advance is the
 * signed byte at func_0201371c(font, glyph)[2]. On return *outC gets the cursor if the line ended
 * at a newline (else 0), and the trailing inter-char opts gap is removed from the width.
 * Called by func_02013814 to find a multi-line string's widest line. */
extern int func_020136d4(int font, int ch);
extern int func_0201371c(int font, int glyph);

int func_02013768(int font, int opts, int s, int *outC)
{
    int c = s;
    int width = 0;
    int (*getNext)(int *) = *(int (**)(int *))(font + 4);
    int ch, glyph;

    ch = getNext(&c);
    while (ch != 0) {
        if (ch == 0xa)
            break;
        glyph = func_020136d4(font, ch);
        if (glyph == 0xffff)
            glyph = *(unsigned short *)(*(int *)font + 2);
        width += opts + (signed char)*(char *)(func_0201371c(font, glyph) + 2);
        ch = getNext(&c);
    }
    if (outC != 0)
        *outC = ch == 0xa ? c : 0;
    if (width > 0)
        width -= opts;
    return width;
}
