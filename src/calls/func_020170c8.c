/* func_020170c8 -- fetch the n-th entry's payload out of a resource dictionary.
 *
 * The file header holds, at +0xc, the byte offset of the slot that holds the block's own
 * offset; the block carries a dictionary at +8 whose entry table starts at a further
 * offset and is preceded by its own 2-byte stride and 4 bytes of header. Each entry
 * begins with the payload's offset from the block. NULL comes back for a NULL file, an
 * out-of-range index, or a dictionary that is not there.
 *
 * Three shape decisions, all visible in the bytes:
 *   - the count and stride are read through the BLOCK pointer (`[ip,#9]`, `[ip,#0xe]`)
 *     while the entry table is built from `&pBlock->dict` (`ip+8`), so the source must
 *     spell those field reads as pBlock->dict.x and never through a dictionary local;
 *   - the guard is `dict && index < count`, not the negated form -- with `||` mwcc lays
 *     the null path in the fall-through and every branch flips;
 *   - the early NULL-file exit shares the single `return 0` tail, which only happens when
 *     the body is nested inside `if (pFile != 0)` rather than returning early. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct ResDict {
    u8  nRevision;
    u8  nEntryCount;
    u16 nDictSize;
    u16 pad_04;
    u16 nEntryTableOffset;
} ResDict;

typedef struct ResBlock {
    u8      pad_00[8];
    ResDict dict;
} ResBlock;

typedef struct ResFile {
    u8  pad_00[0xc];
    u16 nBlockOffsetSlot;
} ResFile;

void *func_020170c8(ResFile *pFile, u32 nIndex)
{
    if (pFile != 0) {
        ResBlock *pBlock = (ResBlock *)((u8 *)pFile
                               + *(u32 *)((u8 *)pFile + pFile->nBlockOffsetSlot));
        u8 *pEntry;

        if (&pBlock->dict != 0 && nIndex < pBlock->dict.nEntryCount) {
            u8 *pTable = (u8 *)&pBlock->dict + pBlock->dict.nEntryTableOffset;

            pEntry = pTable + 4 + *(u16 *)pTable * nIndex;
        } else {
            pEntry = 0;
        }
        if (pEntry != 0) {
            return (u8 *)pBlock + *(u32 *)pEntry;
        }
    }
    return 0;
}
