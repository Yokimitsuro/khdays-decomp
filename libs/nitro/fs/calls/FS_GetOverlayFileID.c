/* FS_GetOverlayFileID: the file of an overlay's image, {&fsi_arc_rom, header.file_id}. The
 * NitroSDK's own form: the struct comes back through the pointer the caller passes in r0. */

#include "nitro/fs.h"

extern FSArchive fsi_arc_rom;

FSFileID FS_GetOverlayFileID(const FSOverlayInfo *p_ovi)
{
    FSFileID ret;
    ret.arc = &fsi_arc_rom;
    ret.file_id = p_ovi->header.file_id;
    return ret;
}
