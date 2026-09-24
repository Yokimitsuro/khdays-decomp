/* MSL __strtoul (kept under its ROM symbol name, which strtol uses): the scanf-style unsigned
 * long reader. Skips white space, takes a sign, a 0 / 0x prefix when the base allows it (base 0
 * picks 8, 10 or 16 from it), then accumulates digits in the base up to `max_width` characters
 * read through ReadProc, flagging overflow past ULONG_MAX. On failure nothing counts as scanned;
 * the first unused character is pushed back. */
#define EOF (-1)
#define ULONG_MAX 0xffffffffUL

enum { __GetAChar, __UngetAChar, __TestForError };

enum scan_states {
    start          = 0x01,
    check_for_zero = 0x02,
    leading_zero   = 0x04,
    need_digit     = 0x08,
    digit_loop     = 0x10,
    finished       = 0x20,
    failure        = 0x40
};

#define final_state(scan_state) (scan_state & (finished | failure))
#define success(scan_state)     (scan_state & (leading_zero | digit_loop | finished))
#define fetch()                 (count++, (*ReadProc)(ReadProcArg, 0, __GetAChar))
#define unfetch(c)              (*ReadProc)(ReadProcArg, c, __UngetAChar)

extern const unsigned char data_02041c48[128];    /* __upper_map */
extern const unsigned short data_02041cc8[128];   /* __ctype_map */

#define __ctype_alpha 0x0001
#define __ctype_digit 0x0008
#define __ctype_space 0x0100

static inline int isalpha(int c)
{
    return (c < 0 || c >= 128) ? 0 : (int)(data_02041cc8[c] & __ctype_alpha);
}

static inline int isdigit(int c)
{
    return (c < 0 || c >= 128) ? 0 : (int)(data_02041cc8[c] & __ctype_digit);
}

static inline int isspace(int c)
{
    return (c < 0 || c >= 128) ? 0 : (int)(data_02041cc8[c] & __ctype_space);
}

static inline int toupper(int c)
{
    return (c < 0 || c >= 128) ? c : data_02041c48[c];
}

unsigned long func_0201fc04(int base, int max_width, int (*ReadProc)(void *, int, int), void *ReadProcArg,
                            int *chars_scanned, int *negative, int *overflow)
{
    int spaces = 0;
    int scan_state = start;
    int count = 0;
    unsigned long value = 0;
    unsigned long value_max = 0;
    int c;

    *negative = *overflow = 0;

    if (base < 0 || base == 1 || base > 36 || max_width < 1)
        scan_state = failure;
    else
        c = fetch();

    if (base != 0)
        value_max = ULONG_MAX / base;

    while (count <= max_width && c != EOF && !final_state(scan_state)) {
        switch (scan_state) {
        case start:
            if (isspace(c)) {
                c = fetch();
                count--;
                spaces++;
                break;
            }

            if (c == '+') {
                c = fetch();
            } else if (c == '-') {
                c = fetch();
                *negative = 1;
            }

            scan_state = check_for_zero;
            break;

        case check_for_zero:
            if (base == 0 || base == 16) {
                if (c == '0') {
                    scan_state = leading_zero;
                    c = fetch();
                    break;
                }
            }

            scan_state = need_digit;
            break;

        case leading_zero:
            if (c == 'X' || c == 'x') {
                base = 16;
                scan_state = need_digit;
                c = fetch();
                break;
            }

            if (base == 0)
                base = 8;

            scan_state = digit_loop;
            break;

        case need_digit:
        case digit_loop:
            if (base == 0)
                base = 10;

            if (!value_max)
                value_max = ULONG_MAX / base;

            if (isdigit(c)) {
                if ((c -= '0') >= base) {
                    if (scan_state == digit_loop)
                        scan_state = finished;
                    else
                        scan_state = failure;

                    c += '0';
                    break;
                }
            } else if (!isalpha(c) || (toupper(c) - 'A' + 10) >= base) {
                if (scan_state == digit_loop)
                    scan_state = finished;
                else
                    scan_state = failure;

                break;
            } else {
                c = toupper(c) - 'A' + 10;
            }

            if (value > value_max)
                *overflow = 1;

            value *= base;

            if (c > (ULONG_MAX - value))
                *overflow = 1;

            value += c;

            scan_state = digit_loop;

            c = fetch();

            break;
        }
    }

    if (!success(scan_state)) {
        count = 0;
        value = 0;
        *chars_scanned = 0;
    } else {
        count--;
        *chars_scanned = count + spaces;
    }

    unfetch(c);

    return value;
}
