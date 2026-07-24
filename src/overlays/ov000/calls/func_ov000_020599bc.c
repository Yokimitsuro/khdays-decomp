/* func_ov000_020599bc -- draw a five-glyph run right-to-left with a one-pixel drop shadow.
 *
 * Walks the run backwards from index 4, advancing x leftwards by 6 per glyph except at index 2
 * (3 -- the separator column is narrower).  Glyph codes 0x34 and 0x3a sit flush; every other
 * code is nudged right by one, or two for 0x31.  Each glyph is drawn twice: once at (x+1, y+1)
 * one depth layer behind (the shadow) and once at (x, y).
 *
 * CODEGEN NOTE -- the two-code guard has to be materialised into a boolean local first
 * (`isPlain = code != 0x34 && code != 0x3a; if (isPlain) ...`).  Testing the condition directly
 * lets mwcc fold it into predicated moves and drop the branch, which is 16 bytes short.
 */
typedef unsigned short u16;

typedef struct Ov000RenderObject Ov000RenderObject;

typedef struct Ov000GlyphRun {
    u16 codes[5];
} Ov000GlyphRun;

extern void func_02030194(Ov000RenderObject *object, int x, int y, int depth, unsigned int code);

void func_ov000_020599bc(Ov000RenderObject *object, const Ov000GlyphRun *run, int x, int y,
                         int depth) {
    int i;

    for (i = 4; i >= 0; i--) {
        int px;
        int isPlain;
        x = x - ((i == 2) ? 3 : 6);
        isPlain = run->codes[i] != 0x34 && run->codes[i] != 0x3a;
        if (isPlain) {
            px = x + ((run->codes[i] == 0x31) ? 2 : 1);
        } else {
            px = x;
        }
        func_02030194(object, px + 1, y + 1, depth - 1, run->codes[i]);
        func_02030194(object, px, y, depth, run->codes[i]);
    }
}
