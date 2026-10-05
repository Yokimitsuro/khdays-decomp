/* Formats the two values into a UTF-16 string with the overlay's template and draws the element
 * with a shadow. */

#include "nitro/types.h"

extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...);
extern void Ov008_DrawElementWithShadow(int p1, int p2, int p3, int p4, int p5, int table);
extern int data_ov008_02090808;

void Ov008_BuildTable20AndDelegate(int p1, int p2, int p3, int p4, int p5, unsigned int p6, unsigned int p7) {
    u16 table[21];
    Text_FormatUtf16(table, 0x14, (const u16 *)&data_ov008_02090808, p6, p7);
    table[20] = 0;
    Ov008_DrawElementWithShadow(p1, p2, p3, p4, p5, (int)table);
}
