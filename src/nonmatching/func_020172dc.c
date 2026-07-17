/*
 * NONMATCHING -- 152/152 bytes, diff @0x5: a load-order/register choice at the head. The ROM keeps
 * the font ctx in r2 and loads ctx[0] BEFORE ctx[0x35], scheduling ctx[0x35] into the ctx[0]->byte
 * load-use delay (`ldr r2,[r1] ; ldr r1,[r2] ; ldr ip,[r2,#0xd4] ; ldrb r3,[r1,#1]`). mwcc reuses r1
 * for ctx and loads ctx[0x35] first (table is used in the guard). Reordering the source locals and
 * flipping the range test to `idx >= table[1]` (done) did not move it. NEXT: force ctx[0] to load
 * before ctx[0x35] while deferring the byte -- the load-delay fill is the real lever. Everything
 * else (the dead `table==0` beq, the entry index math, the metric copy / flag store) is byte-exact.
 * x2 twin in main.
 *
 * func_020172dc (main; x2 twin of func_020172xx). Glyph-metrics lookup.
 * Via the global font context (data_020475d0), pick the character bank ctx[0x35]; if the code
 * point idx = byte at ctx[0]+1 is in range, index the bank's entry table (offset at +6, stride =
 * entry[0], base +4) to reach the glyph record. If the glyph's flag bit0 is clear, publish its
 * three metric words into obj[0x13..0x15]; otherwise flag obj |= 4 (glyph missing).
 */
extern int *data_020475d0;

void func_020172dc(unsigned int *obj) {
    int *ctx = data_020475d0;
    int c0 = ctx[0];
    int table = ctx[0x35];
    unsigned int idx = *(unsigned char *)(c0 + 1);
    unsigned short *g;

    if (table != 0) {
        int *entry;
        if (table == 0 || idx >= (unsigned int)*(unsigned char *)(table + 1)) {
            entry = 0;
        } else {
            entry = (int *)(*(unsigned short *)(table + *(unsigned short *)(table + 6)) * idx +
                            table + *(unsigned short *)(table + 6) + 4);
        }
        if (entry != 0) {
            g = (unsigned short *)(table + *entry);
            goto have;
        }
    }
    g = 0;
have:
    if ((*g & 1) == 0) {
        obj[0x13] = *(unsigned int *)((char *)g + 4);
        obj[0x14] = *(unsigned int *)((char *)g + 8);
        obj[0x15] = *(unsigned int *)((char *)g + 0xc);
        return;
    }
    *obj |= 4;
}
