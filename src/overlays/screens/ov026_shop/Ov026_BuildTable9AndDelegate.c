/* Formats the value into a UTF-16 string with the overlay's template and draws it with a shadow. */

#include "nitro/types.h"

extern void Text_FormatUtf16(u16 *dst, unsigned int len, const u16 *fmt, ...);
extern void Ov026_DrawStringShadowed(int p1, int table, int p3, int p4, int p5, int p6);
extern int data_ov026_0209130c;

void Ov026_BuildTable9AndDelegate(int p1, unsigned int p2, int p3, int p4, int p5) {
    u16 table[9];
    Text_FormatUtf16(table, 9, (const unsigned short *)&data_ov026_0209130c, p2);
    Ov026_DrawStringShadowed(p1, (int)table, p3, p4, p5, 0x20);
}
