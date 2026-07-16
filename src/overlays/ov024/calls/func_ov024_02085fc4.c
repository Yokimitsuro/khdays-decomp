/* func_ov024_02085fc4 -- MobiClip: settle a pending async read on a bitstream cursor.
 * The in-flight flag is at +0x10; when set, wait on the source's FS request. The flag is
 * cleared either way. */
extern void FS_WaitAsync(int *file);

void func_ov024_02085fc4(int cur) {
    if (*(unsigned char *)(cur + 0x10) == 1) {
        FS_WaitAsync(*(int **)(cur + 0xc));
    }
    *(unsigned char *)(cur + 0x10) = 0;
}
