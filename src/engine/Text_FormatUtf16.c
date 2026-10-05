/* Format a UTF-16 string into dst (at most len characters): hands the variadic tail to
 * Text_VSNPrintfWide as a va_list spelled out as the SDK's macro expands it. */
#include "nitro/types.h"

extern int Text_VSNPrintfWide(u16 *dst, unsigned int len, const u16 *fmt, void *vlist);

void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...) {
    Text_VSNPrintfWide(dst, len, fmt, (void *)(((unsigned int)&fmt & ~3u) + 4));
}
