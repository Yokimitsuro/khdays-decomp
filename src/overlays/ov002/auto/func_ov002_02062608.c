/*
 * func_ov002_02062608 - append a u16 list onto another, bounded and null-terminated (ARM, reloc-free).
 *
 * dest is a fixed-capacity array of `limit` u16 slots holding a zero-terminated list; src is a
 * zero-terminated u16 list to append. Phase 1 advances past the existing entries in dest (stopping
 * at the first zero or when `limit` slots have been consumed, returning if full). Phase 2 copies
 * src entries into the remaining slots, always keeping the last slot for a terminating zero: it
 * stops when src ends (writing a final 0) or when only the terminator slot is left (writing 0 and
 * returning). `count` is the shared slot index across both phases.
 */
void func_ov002_02062608(unsigned short *dest, unsigned short *src, int limit)
{
    int count = 0;
    unsigned short val = *dest;
    if (val != 0) {
        do {
            count++;
            dest++;
            if (count >= limit) return;
            val = *dest;
        } while (val != 0);
    }
    val = *src;
    if (val == 0) goto term;
    limit--;
    do {
        count++;
        src++;
        *dest++ = val;
        if (count >= limit) { *dest = 0; return; }
        val = *src;
    } while (val != 0);
term:
    *dest = 0;
}
