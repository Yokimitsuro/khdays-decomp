/* func_ov012_0205be44 -- measure the rendered width of the current MobiClip subtitle.
 * The stream cursors are copied locally, so measurement does not consume the live subtitle. */
typedef struct {
    signed char *metrics;
    unsigned char *bitmap;
} MobiClipGlyphRef;

extern void func_0202fafc(int stream, MobiClipGlyphRef *out, unsigned int codepoint);

int func_ov012_0205be44(int stream) {
    int primaryCursor;
    int stateCursor;
    int state;
    int width;
    unsigned short codepoint;
    signed char *buffer;
    int *cursor;
    MobiClipGlyphRef glyph;
    int offset;
    int ch;
    int nextWidth;

    primaryCursor = *(int *)(stream + 0x64);
    state = *(int *)(stream + 0x6c);
    width = 0;

    for (;;) {
        switch (state) {
        case 0:
            buffer = *(signed char **)(stream + 0x74);
            cursor = &primaryCursor;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            buffer = *(signed char **)(stream + state * 4 + 0x74);
            cursor = &stateCursor;
            break;
        }

        offset = *cursor;
        ch = buffer[offset];
        if (ch == 0) {
            if (state == 0) {
                return width;
            }
            state = 0;
        } else if (ch >= 1 && ch < 0x20) {
            switch (ch) {
            case 8:
                stateCursor = 0;
                state = 1;
                break;
            case 9:
                stateCursor = 0;
                state = 2;
                break;
            case 11:
                stateCursor = 0;
                state = 3;
                break;
            case 12:
                stateCursor = 0;
                state = 4;
                break;
            case 10:
                return width;
            }
            *cursor = *cursor + 1;
        } else {
            if (ch >= 0x20 && ch < 0x80) {
                codepoint = (unsigned short)ch;
                *cursor = *cursor + 1;
            } else if ((ch & 0xe0) == 0xc0) {
                unsigned short cont = (unsigned short)(buffer[*cursor + 1] & 0x3f);
                unsigned short lead = (unsigned short)(ch & 0x1f);
                codepoint = (unsigned short)((lead << 6) | cont);
                *cursor = *cursor + 2;
            } else if ((ch & 0xf0) == 0xe0) {
                codepoint = (unsigned short)(((unsigned short)(buffer[*cursor + 1] & 0x3f) << 6) |
                    ((unsigned short)(ch & 0xf) << 12) |
                    (unsigned short)(buffer[*cursor + 2] & 0x3f));
                *cursor = *cursor + 3;
            }

            func_0202fafc(stream, &glyph, codepoint);
            nextWidth = glyph.metrics[2] + *(int *)(stream + 0x88) + width;
            if (nextWidth > *(int *)(stream + 0x40)) {
                return width;
            }
            width = nextWidth;
        }
    }
}
