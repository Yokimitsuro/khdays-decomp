typedef int (*ArcWrite)(void *arc, void *dst, int off, int len);

/* Advances the file cursor and hands the write to the archive's own write entry (+0x4c). */
int FSi_WriteFileCommand(char *f) {
    char *arc = *(char **)(f + 8);
    int off = *(int *)(f + 0x2c);
    int len = *(int *)(f + 0x38);
    void *dst = *(void **)(f + 0x30);
    *(int *)(f + 0x2c) = off + len;
    return (*(ArcWrite *)(arc + 0x4c))(arc, dst, off, len);
}
