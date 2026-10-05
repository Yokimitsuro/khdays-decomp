/* Formats the value into a UTF-16 string with the overlay's template and draws the element with a
 * shadow. */

#include "nitro/types.h"

extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...);
extern void Ov008_DrawElementWithShadow(int p1, int p2, int p3, int p4, int p5, int table);
extern int data_ov008_020907e8;

void Ov008_BuildTableAndDelegate(int p1, int p2, int p3, int p4, int p5, unsigned int p6) {
    u16 table[11];
    Text_FormatUtf16(table, 10, (const u16 *)&data_ov008_020907e8, p6);
    table[10] = 0;
    Ov008_DrawElementWithShadow(p1, p2, p3, p4, p5, (int)table);
}
