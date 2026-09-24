/* MSL strtol (kept under its ROM symbol name, which the callers use): converts through __strtoul
 * (func_0201fc04) reading the string with __StringRead (func_0201f884), stores the end pointer, and
 * clamps to LONG_MIN / LONG_MAX with errno (data_0204bd7c) = ERANGE on overflow. */
typedef struct {
    char *NextChar;
    int NullCharDetected;
} __InStrCtrl;

extern unsigned long func_0201fc04(int base, int max, int (*ReadProc)(void *, int, int),
                                   void *ReadProcArg, int *chars_scanned, int *negative,
                                   int *overflow);   /* __strtoul */
extern int func_0201f884(void *isc, int ch, int action);   /* __StringRead */
extern int data_0204bd7c;

long func_0201ffec(const char *str, char **end, int base)
{
    unsigned long value;
    int count, negative, overflow;
    __InStrCtrl isc;

    isc.NextChar = (char *)str;
    isc.NullCharDetected = 0;

    value = func_0201fc04(base, 0x7fffffff, func_0201f884, (void *)&isc, &count, &negative, &overflow);

    if (end)
        *end = (char *)str + count;

    if (overflow || (!negative && value > 0x7fffffff) || (negative && value > 0x80000000)) {
        value = (negative ? 0x80000000 : 0x7fffffff);
        data_0204bd7c = 0x22;
    } else if (negative)
        value = -value;

    return (long)value;
}
