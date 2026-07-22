/* Resolves `path` to a file id through a throwaway file handle. */
extern void FS_InitFile(void *file);
extern void *FSi_FindPath(void *file, const char *path, void *idOut, int dir);

int FS_ConvertPathToFileID(void *idOut, const char *path) {
    char file[0x48];
    FS_InitFile(file);
    return FSi_FindPath(file, path, idOut, 0) != 0;
}
