/* func_ov024_02085f48 -- MobiClip: start a read-ahead covering `len` bytes at the cursor.
 * The FS wants 512-aligned work, so this reads the whole span of sectors containing
 * [pos, pos+len): it seeks back to the sector the cursor sits in and rounds the length up to a
 * sector boundary. The return value is the cursor's skew inside that sector, i.e. where the
 * caller's data actually starts in `dst` -- not a status.
 * The cursor's position still advances by only `len`, and +0x10 is flagged so that a later
 * func_ov024_02085ed8 knows to settle the transfer and re-seek before reading normally.
 * Returns 0 if the read could not be issued. */
extern int FS_SeekFile(int file, int pos, int whence);
extern int FS_ReadFileAsync(int file, void *dst, unsigned int len);

int func_ov024_02085f48(int cur, void *dst, unsigned int len) {
    int pos = *(int *)(cur + 8);
    int base = pos & -0x200;
    int skew = pos - base;
    unsigned int total = len + skew;

    if (total & 0x1ff) {
        total = (total & -0x200) + 0x200;
    }
    FS_SeekFile(*(int *)(cur + 0xc), base, 0);
    if (FS_ReadFileAsync(*(int *)(cur + 0xc), dst, total) == -1) {
        return 0;
    }
    *(int *)(cur + 8) += len;
    *(unsigned char *)(cur + 0x10) = 1;
    return skew;
}
