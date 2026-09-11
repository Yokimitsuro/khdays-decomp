/*
 * Widen a UTF-8 string into UCS-2 code units, one u16 per decoded
 * character, terminated with 0. Returns the source length in bytes.
 *
 * Control characters (1..0x1f) and printable ASCII (0x20..0x7f) copy
 * straight through; 2- and 3-byte sequences are decoded. A lead byte that
 * is none of these (a stray continuation byte, a 4-byte lead) is not
 * consumed: the output slot is skipped and the same byte is examined again.
 *
 * The strlen result stays in r0 until the epilogue, which is what pins the
 * final zero store to r1: the function returns the byte length even though
 * every caller in the tree ignores it.
 *
 * Each decoded field is narrowed to u16 before it is shifted into place;
 * that is where the lsl #16 / lsr #(16-n) pairs come from.
 *
 * ARM.
 */

typedef unsigned short u16;

extern int strlen(const char *s);

int func_0202fcb8(const char *src, u16 *dst)
{
    int len;
    int i;
    char c;

    len = strlen(src);
    for (i = 0; i < len; ) {
        c = src[i];
        if (c >= 1 && c < 0x20) {
            *dst = c;
            i++;
        } else if (c >= 0x20 && c < 0x80) {
            *dst = c;
            i++;
        } else if ((c & 0xe0) == 0xc0) {
            *dst = ((u16)(c & 0x1f) << 6) | (src[i + 1] & 0x3f);
            i += 2;
        } else if ((c & 0xf0) == 0xe0) {
            *dst = ((u16)(c & 0xf) << 12) | ((u16)(src[i + 1] & 0x3f) << 6) | (u16)(src[i + 2] & 0x3f);
            i += 3;
        }
        dst++;
    }
    *dst = 0;
    return len;
}
