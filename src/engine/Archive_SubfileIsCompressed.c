/* Archive_SubfileIsCompressed -- whether the subfile a handle names (game/archive.h) is stored
 * compressed: bit 31 of its entry in the archive header's size table. The header (from
 * ARCHIVE_HANDLE_HEADER) keeps its entry count at +2; the size table follows the offset table
 * ((count + 1) / 2 words from +0x10), one word per subfile.
 *
 * The 0xfffffc mask of the two index terms is ONE local: the ROM loads it once and derives the
 * 0x1ff masks from it with `lsr #15`, which is what a shared variable gives for free.
 *
 * The two index terms are deliberately spelled differently and both spellings are load-bearing:
 *  - the count term keeps the explicit `(x << 0x11) >> 0xf` -- it is a 15-bit truncation
 *    followed by *4, and `(unsigned short)x * 4` comes out as a 16-bit one;
 *  - the subfile term goes through an `unsigned short` local, because written as the same
 *    shift pair mwcc folds the mask into the shift (`p << 23 >> 21`) and drops an instruction.
 * The `(e + 1) / 2` is a SIGNED divide -- the ROM's `add r0,r0,r0,lsr#31 ; asr r0,r0,#1`. */

#include "game/archive.h"
unsigned int Archive_SubfileIsCompressed(unsigned int handle) {
    unsigned int mask = 0xfffffc;
    unsigned int base = ARCHIVE_HANDLE_HEADER(handle);
    unsigned short lo = handle & (mask >> 15);
    int e = *(unsigned short *)(base + 2) & (mask >> 15);

    return *(unsigned int *)(base + ((unsigned int)(((e + 1) / 2) << 0x11) >> 0xf)
                                  + lo * 4 + 0x10) & 0x80000000;
}
