typedef int BOOL;

typedef struct { unsigned int arc; unsigned int file_id; } FSFileID;

typedef struct FSFileStruct {
    char _0[0x30];
    int active;          /* +0x30 */
    char _34[0x48];      /* +0x34 .. +0x7b  -- FSFile (size 0x48) */
    FSFileID id;         /* +0x7c .. +0x83 */
    unsigned int field_84;
    unsigned int field_88;
    unsigned int field_8c;
    unsigned int field_90;
} FSFileStruct;

extern void FS_InitFile(void *file);
extern BOOL FS_ConvertPathToFileID(FSFileID *id, const char *path);
extern BOOL FS_OpenFileFast(void *file, FSFileID id);
extern int func_0201b1e8(FSFileStruct *f, int a, int b);

extern FSFileStruct *data_0204ad4c;

void func_0201b168(FSFileStruct *f, const char *path, int a, int b)
{
    f->field_8c = 0;
    f->field_84 = 0;
    f->field_88 = 0;
    f->field_90 = 0;

    if (!FS_ConvertPathToFileID(&f->id, path))
        return;

    FS_InitFile(&f->_34);

    if (!FS_OpenFileFast(&f->_34, f->id))
        return;

    f->active = 1;
    if (func_0201b1e8(f, a, b))
        data_0204ad4c = f;
}
