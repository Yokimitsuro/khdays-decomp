/* FS_LoadArchive -- fill in an FSArchive descriptor's byte-range and
 * read/write callback fields, then mark it loaded (flag bit 2).
 *
 * The archive struct is the same 0x5c-byte descriptor FS_InitArchive
 * zeroes and FS_RegisterArchiveName links onto the archive list (flag
 * bit 0 there). Field +0x28 is the base pointer a memory-backed archive
 * adds its read/write offset to (see FSi_ReadMemCallback / WriteMemCallback,
 * which read it back as arc[10]). The caller may pass 0 for either
 * callback to request the default memory-archive read/write pair.
 *
 * ARM.
 */

typedef int BOOL;
typedef unsigned int u32;

typedef int (*FSArchiveReadProc)(char **arc, void *dst, u32 off, u32 len);
typedef int (*FSArchiveWriteProc)(char **arc, const void *src, u32 off, u32 len);

extern int FSi_ReadMemCallback(char **arc, void *dst, u32 off, u32 len);
extern int FSi_WriteMemCallback(char **arc, const void *src, u32 off, u32 len);

typedef struct {
    char pad00[0x1c];
    u32 flag;                  /* +0x1c */
    char pad20[0x8];
    u32 base;                  /* +0x28 */
    u32 field_2c;               /* +0x2c */
    u32 field_30;               /* +0x30 */
    u32 field_34;               /* +0x34 */
    u32 field_38;               /* +0x38 */
    u32 field_3c;               /* +0x3c */
    u32 field_40;               /* +0x40 */
    u32 field_44;               /* +0x44 */
    FSArchiveReadProc pRead;   /* +0x48 */
    FSArchiveWriteProc pWrite; /* +0x4c */
    u32 field_50;                /* +0x50 */
} FSArchive;

BOOL FS_LoadArchive(FSArchive *arc, u32 p1, u32 p2, u32 p3, u32 p4, u32 p5,
                     FSArchiveReadProc pRead, FSArchiveWriteProc pWrite)
{
    arc->base = p1;
    arc->field_30 = p3;
    arc->field_2c = arc->field_3c = p2;
    arc->field_38 = p5;
    arc->field_34 = arc->field_40 = p4;
    arc->pRead = pRead ? pRead : FSi_ReadMemCallback;
    arc->pWrite = pWrite ? pWrite : FSi_WriteMemCallback;
    arc->field_50 = (u32)arc->pRead;
    arc->field_44 = 0;
    arc->flag |= 2;
    return 1;
}
