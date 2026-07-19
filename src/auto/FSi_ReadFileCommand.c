typedef int (*ArcRead)(void *arc, void *dst, int off, int len);

/* Advances the file cursor and hands the read to the archive's own read entry (+0x48). */
int FSi_ReadFileCommand(char *f) {
    char *arc = *(char **)(f + 8);
    int off = *(int *)(f + 0x2c);
    int len = *(int *)(f + 0x38);
    void *dst = *(void **)(f + 0x30);
    *(int *)(f + 0x2c) = off + len;
    return (*(ArcRead *)(arc + 0x48))(arc, dst, off, len);
}
