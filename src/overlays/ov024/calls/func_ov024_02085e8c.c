/* func_ov024_02085e8c -- MobiClip: seek a bitstream cursor to `pos`.
 * Settles any in-flight async read first (the flag at +0x10), then seeks the source file.
 * On success the cursor's position cache at +8 is updated. */
extern void FS_WaitAsync(int *file, int a, void *b, int c);
extern int  FS_SeekFile(int file, int pos, int whence);

int func_ov024_02085e8c(int cur, int pos, void *b, int c) {
    if (*(unsigned char *)(cur + 0x10) == 1) {
        FS_WaitAsync(*(int **)(cur + 0xc), pos, b, c);
        *(unsigned char *)(cur + 0x10) = 0;
    }
    if (FS_SeekFile(*(int *)(cur + 0xc), pos, 0) == 0) {
        return 0;
    }
    *(int *)(cur + 8) = pos;
    return 1;
}
