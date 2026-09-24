/* Starts a streamed decompression of `file`: the first 0x200-byte block is read into the reader,
 * the header's size (word >> 8) picks the destination (allocated 32-byte aligned from `heap`
 * when none is given, else it must fit in *pSize), *pSize becomes the size and the uncompress
 * context (+0x400) is set up (func_0200443c). The block after the header is fed at once
 * (func_02004484); unless that already finished (*pDone), block 0 of the double buffer is queued
 * with FS_ReadFileAsync. Returns the destination (0 when it does not fit). */
typedef struct FSFile FSFile;

extern int OS_UnlockByWord_0x0200ae4c(FSFile *p_file, void *dst, int len);   /* FS_ReadFile */
extern int FS_ReadFileAsync(FSFile *p_file, void *dst, int len);
extern void *func_020236f8(unsigned size, int align, int **heapPP);
extern void func_0200443c(void *context, void *dest, void *header);
extern int func_02004484(void *context, void *src, int len);
extern char *data_0204bbfc[];

void *func_0201e508(char *rd, FSFile *file, void *dest, int *pSize, int **heap, int unused,
                    int *pDone)
{
    int size;
    char *m = data_0204bbfc[0];

    *(int *)(rd + 0x418) = OS_UnlockByWord_0x0200ae4c(file, rd, 0x200);
    size = *(unsigned *)rd >> 8;
    if (dest == 0) {
        dest = func_020236f8(size, 0x20, heap);
    } else if (size > *pSize) {
        return 0;
    }
    *pSize = size;
    func_0200443c(rd + 0x400, dest, rd);
    *(int *)(m + 0x418) -= 4;
    *pDone = func_02004484(m + 0x400, m + 4, *(int *)(m + 0x418)) == 0;
    if (*pDone == 0) {
        *(unsigned char *)(rd + 0x414) = 0;
        *(unsigned char *)(rd + 0x415) = 1;
        *(int *)(rd + 0x41c) = 0;
        *(int *)(rd + 0x418) = 0;
        ((int *)(rd + 0x418))[*(unsigned char *)(rd + 0x414)] =
            FS_ReadFileAsync(file, rd + (*(unsigned char *)(rd + 0x414) << 9), 0x200);
    }
    return dest;
}
