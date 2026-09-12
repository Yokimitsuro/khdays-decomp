/*
 * func_0201ef9c - load a whole card file into a fresh heap buffer.
 *
 * `name` is either a path (expanded through func_02024e6c) or, with bit 31
 * set, a packed sub-file id opened directly. A file is compressed when the
 * id says so, or when the path ends in ".z"/".Z" (folded through MSL's
 * toupper). Compressed data is streamed through the loader's two 0x200-byte
 * sectors: each turn flips both sector indices, waits for the previous read,
 * queues the next one, and decompresses the sector that just landed until
 * func_02004484 reports it is done. Uncompressed data is read straight into
 * a buffer of the file's length. Either way the pending heap override is
 * cleared, the file closed and the buffer (or 0 on an open failure) returned.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    char pad00[0x24];
    u32 top;
    u32 bottom;
    char pad2c[0x1c];
} FSFile;                          /* 0x48 bytes */

typedef struct {
    u8 sector[2][0x200];
    char decompState[0x14];        /* 0x400 */
    u8 readIdx;                    /* 0x414: sector the next read lands in */
    u8 useIdx;                     /* 0x415: sector being decompressed */
    char pad416[2];
    int readLen[2];                /* 0x418: result of each sector's read */
} LoadStream;

/* Loader globals: [0] the streaming context, [5] a one-shot heap override. */
extern int *data_0204bbfc[];
extern const u8 data_02041c48[128];

extern void FS_InitFile(FSFile *file);
extern void FSi_WaitForCardThread(void);
extern int func_020250bc(FSFile *file, u32 id);
extern u32 func_02025074(u32 id);
extern int strlen(const char *s);
extern char *func_02024e6c(char *name);
extern int FS_OpenFile(FSFile *file, const char *path);
extern void *func_0201e508(LoadStream *stream, FSFile *file, int a, u32 *outSize,
                           int *heap, u32 kind, int *outStatus);
extern void FS_WaitAsync(FSFile *file);
extern int FS_ReadFileAsync(FSFile *file, void *dst, int len);
extern void OS_Terminate(void);
extern int func_02004484(void *state, void *src, int len);
extern void DC_FlushAll(void);
extern void DC_FlushRange(void *addr, u32 len);
extern void *func_020236f8(u32 size, int align, int **heapPP);
extern void OS_UnlockByWord_0x0200ae4c(FSFile *file, void *dst, u32 len);
extern void FS_CloseFile(FSFile *file);

static inline int toupper(int c)
{
    return (c < 0 || c >= 128) ? c : data_02041c48[c];
}

void *func_0201ef9c(char *name, u32 kind)
{
    FSFile file;
    u32 size;
    int status;
    int opened;
    u32 compressed;
    void *buf;
    LoadStream *stream = (LoadStream *)data_0204bbfc[0];

    FS_InitFile(&file);
    FSi_WaitForCardThread();
    if ((u32)name & 0x80000000) {
        opened = func_020250bc(&file, (u32)name);
        compressed = func_02025074((u32)name);
    } else {
        int len = strlen(name);
        opened = FS_OpenFile(&file, func_02024e6c(name));
        compressed = 0;
        if (name[len - 2] == '.' && toupper(name[len - 1]) == 'Z') {
            compressed = 1;
        }
    }
    if (opened == 0) {
        return 0;
    }
    if (compressed != 0) {
        buf = func_0201e508(stream, &file, 0, &size, data_0204bbfc[5], kind, &status);
        if (status == 0) {
            do {
                stream->readIdx ^= 1;
                stream->useIdx ^= 1;
                FS_WaitAsync(&file);
                stream->readLen[stream->readIdx] =
                    FS_ReadFileAsync(&file, stream->sector[stream->readIdx], 0x200);
                if (stream->readLen[stream->useIdx] != 0 &&
                    stream->readLen[stream->useIdx] == -1) {
                    OS_Terminate();
                }
            } while (func_02004484(stream->decompState, stream->sector[stream->useIdx],
                                   stream->readLen[stream->useIdx]) != 0);
        }
        if (size >= 0x2400) {
            DC_FlushAll();
        } else {
            DC_FlushRange(buf, size);
        }
    } else {
        size = file.bottom - file.top;
        buf = func_020236f8(size, 0x20, (int **)data_0204bbfc[5]);
        if (buf != 0) {
            OS_UnlockByWord_0x0200ae4c(&file, buf, size);
        }
    }
    data_0204bbfc[5] = 0;
    FS_CloseFile(&file);
    return buf;
}
