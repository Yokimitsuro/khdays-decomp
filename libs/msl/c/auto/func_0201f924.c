/* MSL strcpy (kept under its ROM symbol name, which the callers use): word-at-a-time copy when source and destination share their alignment, with the
 * usual zero-byte test ((w + 0xfefefeff) & ~w & 0x80808080); bytes otherwise. */
#define K1 0x80808080
#define K2 0xfefefeff

char *func_0201f924(char *dst, const char *src)
{
    register unsigned char *destb, *fromb;
    register unsigned long w, t, align;

    fromb = (unsigned char *)src;
    destb = (unsigned char *)dst;

    if ((align = ((int)fromb & 3)) != ((int)destb & 3)) {
        goto bytecopy;
    }

    if (align) {
        if ((*destb = *fromb) == 0)
            return dst;
        for (align = 3 - align; align; align--) {
            if ((*(++destb) = *(++fromb)) == 0)
                return dst;
        }
        ++destb;
        ++fromb;
    }

    w = *((int *)(fromb));

    t = w + K2;

    t &= ~w;
    t &= K1;
    if (t)
        goto bytecopy;
    --((int *)(destb));

    do {
        *(++((int *)(destb))) = w;
        w = *(++((int *)(fromb)));

        t = w + K2;
        t &= ~w;
        t &= K1;
        if (t)
            goto adjust;
    } while (1);

adjust:
    ++((int *)(destb));
bytecopy:
    if ((*destb = *fromb) == 0)
        return dst;

    do {
        if ((*(++destb) = *(++fromb)) == 0)
            return dst;
    } while (1);

    return dst;
}
