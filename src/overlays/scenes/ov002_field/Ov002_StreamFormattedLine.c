/*
 * Ov002_StreamFormattedLine - format a result line and stream it into the staging buffer.
 * Called from the ov002 gameplay path. Builds a text line for param_1 via
 * Ov002_FormatEventScriptName into a 12-byte stack scratch, encodes it with MsgArchive_FindEntryByName (against
 * the sub-object at ctx+4), then packs a descriptor word and hands it to Stream_DecodeIntoStagingBuffer
 * together with the context's staging buffer (ctx+8) and its tail pointer (ctx+0x859c).
 *
 * ARM. The descriptor packs ((subLen + 0x8000) & 0xfffffc) << 7, with bit31 set and the low
 * bits of the encode result masked in via (0xfffffc >> 15). The single mask constant is kept
 * in a register and reused with lsr #15, so it is written as one literal used twice.
 */

#include "nitro/types.h"
#include "game/archive.h"

extern void Ov002_FormatEventScriptName(int a, char *out);
extern u32  MsgArchive_FindEntryByName(int a, char *b);
extern void Stream_DecodeIntoStagingBuffer(u32 *dst, u32 desc, u32 *src, u8 **staging);
extern int  data_ov002_0207fa00;

void Ov002_StreamFormattedLine(int param_1, u32 *param_2)
{
    char *ctx = (char *)data_ov002_0207fa00;
    char local[12];
    u32 v;

    Ov002_FormatEventScriptName(param_1, local);
    v = MsgArchive_FindEntryByName(*(int *)(ctx + 4), local);
    Stream_DecodeIntoStagingBuffer(
        (u32 *)(ctx + 8),
        ARCHIVE_HANDLE(*(int *)(ctx + 4), v & (0xfffffc >> 15)),
        param_2,
        (u8 **)(ctx + 0x859c));
}
