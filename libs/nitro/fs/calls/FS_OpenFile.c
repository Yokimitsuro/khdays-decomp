/* Resolves the path and opens the file it names.
 *
 * The id pair is a two-word STRUCT passed by value: that is what makes the ROM load both
 * halves with one `ldm r1,{r1,r2}` instead of two ldr.  And both failure paths share one
 * `return 0`, so the first has to reach it with a goto. */
struct FileID {
    unsigned int arc;
    unsigned int id;
};

extern int FS_ConvertPathToFileID(struct FileID *id, const char *path);
extern int FS_OpenFileFast(void *file, struct FileID id);

int FS_OpenFile(void *file, const char *path) {
    struct FileID id;
    if (FS_ConvertPathToFileID(&id, path) == 0) {
        goto no;
    }
    if (FS_OpenFileFast(file, id) != 0) {
        return 1;
    }
no:
    return 0;
}
