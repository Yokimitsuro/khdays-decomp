/* Case-insensitive compare of at most `n` characters: ASCII characters are folded through the
 * data_02041bc8 case table (bytes outside 0..0x7f compare as they are). Returns -1 / 1 at the first
 * difference and 0 at a common terminator or after `n` characters. */
extern const unsigned char data_02041bc8[];

static inline int FoldCase(int c)
{
    if (c < 0 || c >= 0x80) {
        return c;
    }
    return data_02041bc8[c];
}

int func_0201f7bc(const signed char *a, const signed char *b, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        signed char ca = FoldCase(*a++);
        signed char cb = FoldCase(*b++);

        if (ca < cb) {
            return -1;
        }
        if (ca > cb) {
            return 1;
        }
        if (ca == 0) {
            return 0;
        }
    }
    return 0;
}
