/* func_ov024_02085ed8 -- MobiClip: synchronous read of `len` bytes from a bitstream cursor.
 * If a read-ahead issued by func_ov024_02085f48 is still in flight (the flag at +0x10), settle
 * it and put the file back where this cursor thinks it is, since the read-ahead left the file
 * positioned at a 512-aligned boundary rather than at the cursor's own position (+8).
 * The cursor's position only advances by what the caller asked for; a short/failed read
 * reports 0 and leaves it alone.
 *
 * OS_UnlockByWord_0x0200ae4c is the delinked name for the routine at 0x0200ae4c; by its use
 * here (file, buffer, length) -> bytes-or-(-1) it is the blocking file read, not a lock op. */
extern void FS_WaitAsync(int file);
extern int  FS_SeekFile(int file, int pos, int whence);
extern int  OS_UnlockByWord_0x0200ae4c(int file, void *dst, unsigned int len);

int func_ov024_02085ed8(int cur, void *dst, unsigned int len) {
    if (*(unsigned char *)(cur + 0x10) == 1) {
        FS_WaitAsync(*(int *)(cur + 0xc));
        FS_SeekFile(*(int *)(cur + 0xc), *(int *)(cur + 8), 0);
        *(unsigned char *)(cur + 0x10) = 0;
    }
    if (OS_UnlockByWord_0x0200ae4c(*(int *)(cur + 0xc), dst, len) == -1) {
        return 0;
    }
    *(int *)(cur + 8) += len;
    return 1;
}
