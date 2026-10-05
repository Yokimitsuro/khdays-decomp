/* Formats the value into a UTF-16 string with the overlay's template and draws it with a shadow. */

#include "nitro/types.h"

extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...);
extern void Text_DrawWithShadow(int p1, int p2, int p3, int p4, int table, int p5);
extern int data_ov025_020b52c4;

void Ov025_BuildTable11AndDelegate(int p1, int p2, int p3, int p4, int p5, unsigned int p6) {
    u16 table[12];
    Text_FormatUtf16(table, 0xb, (const unsigned short *)&data_ov025_020b52c4, p6);
    table[11] = 0;
    Text_DrawWithShadow(p1, p2, p3, p4, (int)table, p5);
}
