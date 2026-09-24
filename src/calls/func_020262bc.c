#pragma thumb on
/* func_020262bc -- vsnprintf into a wide (u16) buffer, MAIN (THUMB). The u16 twin of func_02025aac
 * (the NitroSDK's STD_TVSNPrintf plus %f for 20.12 fixed point, formatted by func_02025a50), without
 * the SJIS double-byte pass. Returns the length in characters the full text would have; %n stores
 * the length in bytes. Only the %c padding uses wide literals, the other characters stay char. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;
typedef unsigned int size_t;

typedef char *va_list;
#define __fourbytealign(n) ((((unsigned long)(n)) + 3U) & ~3U)
#define va_arg(ap, type) (*(type *)(((ap) += __fourbytealign(sizeof(type))) - __fourbytealign(sizeof(type))))

typedef struct dst_string_tag {
    size_t len;
    u16 *cur;
    u16 *base;
} dst_string;

extern void func_02025818(dst_string *p, u16 c);                    /* string_put_char */
extern void func_02025860(dst_string *p, u16 c, int n);             /* string_fill_char */
extern void func_020258c4(dst_string *p, const u16 *s, int n);      /* string_put_string */
extern void func_02025a50(s64 value, int precision, u16 *pIntText, u16 *pFracText);
extern u32 func_020200c8(const u16 *str);                           /* wide string length */

#define string_put_char func_02025818
#define string_fill_char func_02025860
#define string_put_string func_020258c4

int func_020262bc(u16 *dst, size_t len, const u16 *fmt, va_list vlist)
{
    u16 buf[24];
    u16 frac[14];
    int n_buf;
    u16 prefix[2];
    int n_prefix;

    const u16 *s = fmt;

    dst_string str;
    str.len = len, str.cur = str.base = dst;

    while (*s) {
        if (*s != '%') {
            string_put_char(&str, *s++);
        } else {
            enum {
                flag_blank = 000001,
                flag_plus = 000002,
                flag_sharp = 000004,
                flag_minus = 000010,
                flag_zero = 000020,
                flag_l1 = 000040,
                flag_h1 = 000100,
                flag_l2 = 000200,
                flag_h2 = 000400,
                flag_unsigned = 010000,
                flag_end
            };
            int flag = 0, width = 0, precision = -1, radix = 10;
            char hex_char = 'a' - 10;
            const u16 *p_start = s;

            for (;;) {
                switch (*++s) {
                case '+':
                    flag |= flag_plus;
                    continue;
                case ' ':
                    flag |= flag_blank;
                    continue;
                case '-':
                    flag |= flag_minus;
                    continue;
                case '0':
                    flag |= flag_zero;
                    continue;
                }
                break;
            }

            if (*s == '*') {
                ++s, width = va_arg(vlist, int);
                if (width < 0)
                    width = -width, flag |= flag_minus;
            } else {
                while ((*s >= '0') && (*s <= '9'))
                    width = (width * 10) + *s++ - '0';
            }

            if (*s == '.') {
                ++s, precision = 0;
                if (*s == '*') {
                    ++s, precision = va_arg(vlist, int);
                    if (precision < 0)
                        precision = -1;
                } else {
                    while ((*s >= '0') && (*s <= '9'))
                        precision = (precision * 10) + *s++ - '0';
                }
            }

            switch (*s) {
            case 'h':
                if (*++s != 'h')
                    flag |= flag_h1;
                else
                    ++s, flag |= flag_h2;
                break;
            case 'l':
                if (*++s != 'l')
                    flag |= flag_l1;
                else
                    ++s, flag |= flag_l2;
                break;
            }

            switch (*s) {
            case 'd':
            case 'i':
                goto put_integer;
            case 'o':
                radix = 8;
                flag |= flag_unsigned;
                goto put_integer;
            case 'u':
                flag |= flag_unsigned;
                goto put_integer;
            case 'X':
                hex_char = 'A' - 10;
                goto put_hexadecimal;
            case 'x':
                goto put_hexadecimal;
            case 'p':
                flag |= flag_sharp;
                precision = 8;
                goto put_hexadecimal;
            case 'c':
                if (precision >= 0)
                    goto put_invalid;
                {
                    int c = va_arg(vlist, int);
                    width -= 1;
                    if (flag & flag_minus) {
                        string_put_char(&str, (u16)c);
                        string_fill_char(&str, ' ', width);
                    } else {
                        u16 pad = (u16)((flag & flag_zero) ? L'0' : L' ');
                        string_fill_char(&str, pad, width);
                        string_put_char(&str, (u16)c);
                    }
                    ++s;
                }
                break;
            case 's':
            {
                int n_buf = 0;
                const u16 *p_buf = va_arg(vlist, const u16 *);
                if (precision < 0) {
                    while (p_buf[n_buf])
                        ++n_buf;
                } else {
                    while ((n_buf < precision) && p_buf[n_buf])
                        ++n_buf;
                }
                width -= n_buf;
                if (flag & flag_minus) {
                    string_put_string(&str, p_buf, n_buf);
                    string_fill_char(&str, ' ', width);
                } else {
                    char pad = (char)((flag & flag_zero) ? '0' : ' ');
                    string_fill_char(&str, pad, width);
                    string_put_string(&str, p_buf, n_buf);
                }
                ++s;
            }
            break;
            case 'n':
            {
                int pos = (char *)str.cur - (char *)str.base;
                if (flag & flag_h2)
                    ;
                else if (flag & flag_h1)
                    *va_arg(vlist, signed short *) = (signed short)pos;
                else if (flag & flag_l2)
                    *va_arg(vlist, u64 *) = (u64)pos;
                else
                    *va_arg(vlist, signed int *) = (signed int)pos;
            }
                ++s;
                break;
            case '%':
                if (p_start + 1 != s)
                    goto put_invalid;
                string_put_char(&str, *s++);
                break;
            default:
                goto put_invalid;
put_invalid:
                string_put_string(&str, p_start, s - p_start);
                break;
            case 'f':
            {
                s64 val;

                n_prefix = 0;
                if (precision < 0)
                    precision = 6;
                if (precision > 8)
                    precision = 8;
                if (flag & (flag_l1 | flag_l2))
                    val = va_arg(vlist, s64);
                else
                    val = va_arg(vlist, long);
                if ((val >> 32) & 0x80000000) {
                    val = ~val + 1;
                    prefix[0] = '-';
                    n_prefix = 1;
                } else if (flag & flag_plus) {
                    prefix[0] = '+';
                    n_prefix = 1;
                } else if (flag & flag_blank) {
                    prefix[0] = ' ';
                    n_prefix = 1;
                }
                func_02025a50(val, precision, buf, frac);
                if (n_prefix + (func_020200c8(buf) + func_020200c8(frac)) + 1 < width)
                    string_fill_char(&str, ' ', width - (n_prefix + (func_020200c8(buf) + func_020200c8(frac)) + 1));
                if (n_prefix > 0)
                    string_put_char(&str, prefix[0]);
                string_put_string(&str, buf, func_020200c8(buf));
                if (frac[0] != 0) {
                    string_put_char(&str, '.');
                    string_put_string(&str, frac, func_020200c8(frac));
                }
                ++s;
            }
            break;
put_hexadecimal:
                radix = 16;
                flag |= flag_unsigned;
put_integer:
                {
                    u64 val = 0;
                    n_prefix = 0;

                    if (flag & flag_minus)
                        flag &= ~flag_zero;
                    if (precision < 0)
                        precision = 1;
                    else
                        flag &= ~flag_zero;

                    if (flag & flag_unsigned) {
                        if (flag & flag_h2)
                            val = va_arg(vlist, unsigned char);
                        else if (flag & flag_h1)
                            val = va_arg(vlist, unsigned short);
                        else if (flag & flag_l2)
                            val = va_arg(vlist, u64);
                        else
                            val = va_arg(vlist, unsigned long);
                        flag &= ~(flag_plus | flag_blank);
                        if (flag & flag_sharp) {
                            if (radix == 16) {
                                if (val != 0) {
                                    prefix[0] = (char)(hex_char + (10 + 'x' - 'a'));
                                    prefix[1] = '0';
                                    n_prefix = 2;
                                }
                            } else if (radix == 8) {
                                prefix[0] = '0';
                                n_prefix = 1;
                            }
                        }
                    } else {
                        if (flag & flag_h2)
                            val = va_arg(vlist, char);
                        else if (flag & flag_h1)
                            val = va_arg(vlist, short);
                        else if (flag & flag_l2)
                            val = va_arg(vlist, u64);
                        else
                            val = va_arg(vlist, long);
                        if ((val >> 32) & 0x80000000) {
                            val = ~val + 1;
                            prefix[0] = '-';
                            n_prefix = 1;
                        } else {
                            if (val || precision) {
                                if (flag & flag_plus) {
                                    prefix[0] = '+';
                                    n_prefix = 1;
                                } else if (flag & flag_blank) {
                                    prefix[0] = ' ';
                                    n_prefix = 1;
                                }
                            }
                        }
                    }
                    n_buf = 0;
                    switch (radix) {
                    case 8:
                        while (val != 0) {
                            int d = (int)(val & 0x07);
                            val >>= 3;
                            buf[n_buf++] = (u16)(d + '0');
                        }
                        break;
                    case 10:
                        if ((val >> 32) == 0) {
                            u32 v = (u32)val;
                            while (v != 0) {
                                u32 r = v / 10;
                                int d = (int)(v - (r * 10));
                                v = r;
                                buf[n_buf++] = (u16)(d + '0');
                            }
                        } else {
                            while (val != 0) {
                                s64 r = val / 10;
                                int d = (int)(val - (r * 10));
                                val = r;
                                buf[n_buf++] = (u16)(d + '0');
                            }
                        }
                        break;
                    case 16:
                        while (val != 0) {
                            int d = (int)(val & 0x0f);
                            val >>= 4;
                            buf[n_buf++] = (u16)((d < 10) ? (d + '0') : (d + hex_char));
                        }
                        break;
                    }
                    if ((n_prefix > 0) && (prefix[0] == '0')) {
                        n_prefix = 0;
                        buf[n_buf++] = '0';
                    }
                }
                goto put_to_stream;
put_to_stream:
                {
                    int n_pad = precision - n_buf;
                    if (flag & flag_zero) {
                        if (n_pad < width - n_buf - n_prefix)
                            n_pad = width - n_buf - n_prefix;
                    }
                    if (n_pad > 0)
                        width -= n_pad;
                    width -= n_prefix + n_buf;
                    if (!(flag & flag_minus))
                        string_fill_char(&str, ' ', width);
                    while (n_prefix > 0)
                        string_put_char(&str, prefix[--n_prefix]);
                    string_fill_char(&str, '0', n_pad);
                    while (n_buf > 0)
                        string_put_char(&str, buf[--n_buf]);
                    if (flag & flag_minus)
                        string_fill_char(&str, ' ', width);
                    ++s;
                }
                break;
            }
        }
    }

    if (str.len > 0) {
        *str.cur = '\0';
    } else if (len > 0) {
        *(str.base + len - 1) = '\0';
    }

    return str.cur - str.base;
}
#pragma thumb off
