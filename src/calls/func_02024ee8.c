/* func_02024ee8 -- load a "db_<lang>.p2" style resource table.
 *
 * func_02024e6c expands the caller's name into the real path; the file's 16-byte
 * header is read first, and its halfword at +2 carries the record count in bits
 * 0-8 and a flag in bit 15. The record table that follows the header is sized as
 * count * 4 bytes, plus 2 bytes per record with the record count rounded up to an
 * even number, plus another count * 8 bytes when the flag is set. A buffer of that
 * size plus the 16-byte header is taken from the default expanding heap, the header
 * is copied into it, word 1 is replaced by the caller's mode, word 2 takes the file's
 * start offset and word 3 is rebased onto the file's image base, and the record
 * table is read in directly behind the header. The file is closed and the buffer
 * returned; the caller owns it.
 */
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 word[4];
} FileHeader;

extern void FS_InitFile(void *f);
extern void FSi_WaitForCardThread(void);
extern char *func_02024e6c(char *name);
extern int FS_OpenFile(void *f, const char *path);
extern int OS_UnlockByWord_0x0200ae4c(void *file, void *buf, int size);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern int FS_CloseFile(void *f);

void *func_02024ee8(const char *name, int mode)
{
    u32 file[0x12];          /* FSFile: [2] = start offset, [9] = image base */
    FileHeader header;
    u16 count;
    u32 size;
    u32 *buf;

    FS_InitFile(file);
    FSi_WaitForCardThread();
    FS_OpenFile(file, func_02024e6c((char *)name));
    OS_UnlockByWord_0x0200ae4c(file, &header, 0x10);

    {
        u16 countAndFlags = *(u16 *)((char *)&header + 2);
        u16 evenCount;

        count = countAndFlags & 0x1ff;
        evenCount = (count + 1) / 2 * 2;
        size = (u16)(evenCount * 2 + count * 4);
        if (countAndFlags & 0x8000) {
            size = (u16)(size + count * 8);
        }
    }

    buf = (u32 *)NNS_FndAllocFromDefaultExpHeapEx((u16)(size + 0x10), 4);
    *(FileHeader *)buf = header;
    buf[1] = mode;
    buf[2] = file[2];
    buf[3] = buf[3] + file[9];
    OS_UnlockByWord_0x0200ae4c(file, buf + 4, size);
    FS_CloseFile(file);
    return buf;
}
