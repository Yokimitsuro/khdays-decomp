/* func_0201386c -- Text_MeasureBlock (148 B, 1 reloc).
 * Measures a multi-line UTF-16 string and writes {maxWidth, totalHeight} to *out. Walks the string
 * line by line with Text_MeasureLineWidth (func_02013768), which advances the cursor and returns a
 * line's pixel width; tracks the widest line and counts the lines. The height is
 * (lineCount - 1) * (spacing + fontLineHeight) - spacing, where fontLineHeight is the signed byte
 * at (*font + 1). Used by the text anchor func_0201449c. */
typedef struct { int w, h; } TextDims;

extern int func_02013768(int *font, int opts, int str, int *out);

void func_0201386c(TextDims *out, int *font, int opts, int spacing, int str)
{
    TextDims dims = {0, 0};
    int lines = 1;
    int w;

    if (str != 0) {
        do {
            w = func_02013768(font, opts, str, &str);
            if (w > dims.w)
                dims.w = w;
            lines++;
        } while (str != 0);
    }
    dims.h = (lines - 1) * (spacing + *(signed char *)(*font + 1)) - spacing;
    *out = dims;
}
