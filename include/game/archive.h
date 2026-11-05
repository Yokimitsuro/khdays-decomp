#ifndef GAME_ARCHIVE_H
#define GAME_ARCHIVE_H

/* A file handle naming a subfile of a packed archive that is already in memory.
 *
 * Archive_LoadFile and the loaders take either a file name or such a handle: bit 31 set, the
 * archive header's address in bits 9-30 and the subfile's index in bits 0-8. The address is kept
 * as 24 bits counted from ARCHIVE_HANDLE_BASE, word-aligned ((header + 0x8000) & 0xfffffc is
 * header - 0x01ff8000 modulo 16 MB, since 0x01ff8000 + 0x8000 is 0x02000000), so a header can lie
 * anywhere in the DS's 16 MB main RAM window from 0x01ff8000: that window is the bound.
 * Archive_OpenSubfileByHandle and Archive_SubfileIsCompressed read it back with
 * ARCHIVE_HANDLE_HEADER and ARCHIVE_HANDLE_INDEX. */

#include "nitro/types.h"

#define ARCHIVE_HANDLE_BASE 0x01ff8000
#define ARCHIVE_HANDLE_MASK 0x00fffffc

#define ARCHIVE_HANDLE(header, index) \
    (((((u32)(header) + 0x8000) & ARCHIVE_HANDLE_MASK) << 7) | 0x80000000 | (index))

#define ARCHIVE_HANDLE_HEADER(handle) ((((u32)(handle) >> 7) & ARCHIVE_HANDLE_MASK) + ARCHIVE_HANDLE_BASE)
#define ARCHIVE_HANDLE_INDEX(handle) ((u32)(handle) & 0x1ff)

#endif
