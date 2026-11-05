/* Opens a file inside a packed archive by its handle (game/archive.h): the handle names the archive
 * header (ARCHIVE_HANDLE_HEADER) and the subfile (ARCHIVE_HANDLE_INDEX), whose offset and size are
 * read from the header's tables. */

#include "nitro/types.h"
#include "game/archive.h"

typedef struct FSArchive FSArchive;
typedef struct FSFile FSFile;
typedef struct FSFileID FSFileID;

extern BOOL FS_OpenFileDirect(FSFile *file, FSArchive *archive, u32 image_top, u32 image_bot, FSFileID *id);

BOOL Archive_OpenSubfileByHandle(FSFile *file, u32 id)
{
    u32 mask = 0x00fffffc;
    u32 base = ARCHIVE_HANDLE_HEADER(id);
    u16 idx  = (u16)ARCHIVE_HANDLE_INDEX(id);
    u8 *p = (u8 *)base;
    u32 top = *(u32 *)(p + 0xc) + ((u32)*(u16 *)(p + idx * 2 + 0x10) << 9);
    FSArchive *arc = *(FSArchive **)(p + 8);
    s32 half = (s32)((*(u16 *)(p + 2) & (mask >> 15)) + 1) / 2;
    u8 *q = p + (u32)((u16)(half * 2)) * 2;
    u32 raw = *(u32 *)(q + idx * 4 + 0x10) & 0x7fffffff;
    return FS_OpenFileDirect(file, arc, top, top + raw, (FSFileID *)0);
}
