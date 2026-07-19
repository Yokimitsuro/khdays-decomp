/* Case-insensitive compare of at most n bytes; only A-Z are folded. */
int FSi_StrNICmp(const char *a, const char *b, unsigned n) {
    unsigned i = 0;
    while (i < n) {
        unsigned ca = (unsigned)(unsigned char)a[i] - 0x41;
        unsigned cb = (unsigned)(unsigned char)b[i] - 0x41;
        if (ca <= 0x19) {
            ca += 0x20;
        }
        if (cb <= 0x19) {
            cb += 0x20;
        }
        if (ca != cb) {
            return (int)(ca - cb);
        }
        i++;
    }
    return 0;
}
