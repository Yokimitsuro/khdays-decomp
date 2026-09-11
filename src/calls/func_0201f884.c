/* func_0201f884 -- character-stream cursor control (ARM).
 * cmd 0: read next byte from the string at pos; on the terminator, set eof
 *   and return -1, else advance pos and return the byte (0-255).
 * cmd 1: push back one byte -- if eof was set, just clear it and return c;
 *   otherwise step pos back one byte and return c.
 * cmd 2: return the eof flag.
 * default: return 0.
 */
typedef struct {
    signed char *pos;
    int eof;
} CharCursor;

int func_0201f884(CharCursor *s, int c, int cmd) {
    switch (cmd) {
    case 0: {
        signed char *p = s->pos;
        int ch = *p;
        if (ch == 0) {
            s->eof = 1;
            return -1;
        }
        s->pos = p + 1;
        return ch & 0xff;
    }
    case 1:
        if (s->eof == 0) {
            s->pos = s->pos - 1;
        } else {
            s->eof = 0;
        }
        return c;
    case 2:
        return s->eof;
    default:
        return 0;
    }
}
