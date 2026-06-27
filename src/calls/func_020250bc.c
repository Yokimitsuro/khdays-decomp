typedef int BOOL;
typedef int s32;
typedef short s16;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct FSArchive FSArchive;
typedef struct FSFile FSFile;
typedef struct FSFileID FSFileID;

extern BOOL FS_OpenFileDirect(FSFile *file, FSArchive *archive, u32 image_top, u32 image_bot, FSFileID *id);

BOOL func_020250bc(FSFile *file, u32 id)
{
    u32 mask = 0x00fffffc;
    u32 base = ((id >> 7) & mask) + 0x01ff8000;
    u16 idx  = (u16)(id & (mask >> 15));
    u8 *p = (u8 *)base;
    u32 top = *(u32 *)(p + 0xc) + ((u32)*(u16 *)(p + idx * 2 + 0x10) << 9);
    FSArchive *arc = *(FSArchive **)(p + 8);
    s32 half = (s32)((*(u16 *)(p + 2) & (mask >> 15)) + 1) / 2;
    u8 *q = p + (u32)((u16)(half * 2)) * 2;
    u32 raw = *(u32 *)(q + idx * 4 + 0x10) & 0x7fffffff;
    return FS_OpenFileDirect(file, arc, top, top + raw, (FSFileID *)0);
}
