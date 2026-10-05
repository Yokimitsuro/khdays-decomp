/* Formats the value into a UTF-16 string with the overlay's template and draws it with a shadow. */

#include "nitro/types.h"

extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...);
extern void Ov008_DrawStringShadowed(int p1, int table, int p3, int p4, int p5, int p6);
extern int data_ov008_02090ea0;

void Ov008_BuildTable9AndDelegate(int p1, unsigned int p2, int p3, int p4, int p5) {
    u16 table[9];
    Text_FormatUtf16(table, 9, (const u16 *)&data_ov008_02090ea0, p2);
    Ov008_DrawStringShadowed(p1, (int)table, p3, p4, p5, 0x20);
}
