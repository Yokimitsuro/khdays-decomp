/*
 * func_ov002_0205287c -- x3 (ov002/...). Variadic thin wrapper around Ov002_MapAndForwardEntry
 * (020528b8): forward the four named args plus a va_list pointing at the trailing arguments, and
 * return the entry pointer `c`.
 *
 * Variadic: mwcc has no stdarg.h on this include path, so the APCS va macros are inlined. va_start
 * here aligns &last down to 4 then adds 4 -- that is the ROM's `add r3,sp,#0x1c; bic r3,#3; add r3,#4`.
 */
typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))

extern int func_ov002_020528b8(int a, unsigned b, unsigned short *c, unsigned d, void *va);

unsigned short *func_ov002_0205287c(int a, unsigned b, unsigned short *c, unsigned d, ...) {
    va_list ap;

    va_start(ap, d);
    func_ov002_020528b8(a, b, c, d, ap);
    return c;
}
