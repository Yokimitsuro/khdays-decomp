/*
 * DC_FlushRange - clean (write back) and invalidate the data cache over
 * [address, address + size), one 32-byte cache line at a time.
 *
 * The ARM9's CP15 "drain write buffer" and "clean and invalidate DCache
 * line by MVA" operations have no mwcc 3.0 intrinsic (every spelling
 * lowers to an external call), so each is written as the project's
 * one-line inline-asm helper, the same convention already used for clz
 * in func_02031440.c / func_02031130.c.
 */

static inline void ZeroIp(void) { asm { mov ip, #0 } }
static inline void DrainWriteBuffer(void) { asm { mcr p15, 0, ip, c7, c10, 4 } }
static inline void CleanAndInvalidateDCacheLine(void *addr) { asm { mcr p15, 0, addr, c7, c14, 1 } }

void DC_FlushRange(void *address, unsigned int size)
{
    int end;
    void *line;

    ZeroIp();
    end = (int)size + (int)address;
    line = (void *)((unsigned int)address & ~0x1f);
    do {
        DrainWriteBuffer();
        CleanAndInvalidateDCacheLine(line);
        line = (char *)line + 0x20;
    } while ((int)line < end);
}
