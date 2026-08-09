/* Packs up to 4 name bytes into a word, one per byte, lowercasing A-Z on the way. */
unsigned FSi_GetPackedName(const char *name, int len) {
    unsigned packed = 0;
    if (len <= 3) {
        int i = 0;
        if (len > 0) {
            int shift = 0;
            do {
                unsigned c = (unsigned char)name[i];
                if (c == 0) {
                    break;
                }
                {
                    int d = (int)c - 0x41;
                    if ((unsigned)d <= 0x19) {
                        c = (unsigned)(d + 0x61);
                    } else {
                        c = (unsigned)(d + 0x41);
                    }
                }
                i++;
                packed |= c << shift;
                shift += 8;
            } while (i < len);
        }
    }
    return packed;
}
