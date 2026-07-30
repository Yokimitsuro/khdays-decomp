/*
 * MsgQueue_Contains - is a message with handle `id` still queued?
 *
 * The message pool (base = *data_0204c230) keeps a 32-bit slot bitmask at +0xc,
 * where a SET bit marks a FREE slot and a CLEAR bit an OCCUPIED one (bit 31 =
 * slot 0). The 6-byte slots start at base+0x10 (MsgSlot: u16 handle, u16 size,
 * u8 type, u8 flags); the per-slot handle at +0 is what the allocator returns.
 *
 * We scan the occupied slots (the complement of the free mask) from the top bit
 * down, clearing each visited bit, and return 1 as soon as a slot's handle
 * equals `id`, else 0. clz selects the next occupied slot index each step.
 *
 * The DS `clz` instruction has no mwcc 3.0 intrinsic (every spelling lowers to
 * an external call), so the leading-zero count is written as a one-line inline
 * asm helper -- the minimal primitive needed for the byte-exact match.
 */

static inline unsigned int Clz(unsigned int x) { asm { clz x, x } return x; }

extern int *data_0204c230;

int func_02031440(unsigned int id)
{
    int *base = data_0204c230;
    char *slots = (char *)base + 0xc;
    unsigned int used = ~*(unsigned int *)slots;
    int idx;

    idx = Clz(used);
    while (idx < 0x20) {
        if (id == *(unsigned short *)(slots + idx * 6 + 4))
            return 1;
        used = used & ~(0x80000000U >> idx);
        idx = Clz(used);
    }
    return 0;
}
