/* func_0201f1a8 -- load a file into a caller buffer synchronously, MAIN. The file (an id with bit 31
 * set, or a path whose language placeholder func_02024e6c expands) is opened. A ".?Z" name or a
 * compressed id is decompressed straight into `buffer` through the streaming reader data_0204bbfc[0]:
 * func_0201e508 starts it, then the two 0x200-byte halves swap, the next block is queued with
 * FS_ReadFileAsync and the finished one is fed to the uncompressor (func_02004484) until it reports
 * the end (a failed read terminates the thread); the data cache is then flushed (all of it past
 * 0x2400 bytes). Anything else is read raw when it fits in `size`. Returns the byte count, or -1
 * when the data does not fit. */
typedef unsigned int u32;
typedef struct FSFile FSFile;

extern void FS_InitFile(void *file);
extern void FSi_WaitForCardThread(void);
extern int func_020250bc(void *file, u32 id);
extern u32 func_02025074(u32 param_1);
extern int strlen(const char *s);
extern char *func_02024e6c(char *name);
extern int FS_OpenFile(void *file, const char *path);
extern void *func_0201e508(char *rd, FSFile *file, void *dest, int *pSize, int **heap, int unused,
                           int *pDone);
extern int FS_WaitAsync(void *file);
extern int FS_ReadFileAsync(void *file, void *dst, int len);
extern void OS_Terminate(void);
extern int func_02004484(void *context, void *src, int len);
extern void DC_FlushAll(void);
extern void DC_FlushRange(const void *startAddr, u32 nBytes);
extern int OS_UnlockByWord_0x0200ae4c(void *file, void *dst, int len);   /* FS_ReadFile */
extern int FS_CloseFile(void *file);
extern char *data_0204bbfc[];
extern const unsigned char data_02041c48[128];

static inline int toupper(int c)
{
    return (c < 0 || c >= 128) ? c : data_02041c48[c];
}

static inline void FlushLoaded(void *buffer, u32 size)
{
    if (size >= 0x2400) {
        DC_FlushAll();
    } else {
        DC_FlushRange(buffer, size);
    }
}

int func_0201f1a8(const void *data, void *buffer, int size)
{
    u32 file[0x12];
    int done;
    int flag;
    int len;
    char *rd = data_0204bbfc[0];

    FS_InitFile(file);
    FSi_WaitForCardThread();

    if ((u32)data & 0x80000000) {
        func_020250bc(file, (u32)data);
        flag = (int)func_02025074((u32)data);
    } else {
        int nameLen = strlen((const char *)data);
        FS_OpenFile(file, func_02024e6c((char *)data));

        flag = 0;
        if (((const char *)data)[nameLen - 2] == '.' &&
            toupper(((const char *)data)[nameLen - 1]) == 'Z') {
            flag = 1;
        }
    }

    if (flag != 0) {
        func_0201e508(rd, (FSFile *)file, buffer, &size, 0, 0, &done);
        len = size;
        if (done == 0) {
            do {
                *(unsigned char *)(rd + 0x414) ^= 1;
                *(unsigned char *)(rd + 0x415) ^= 1;
                FS_WaitAsync(file);
                ((int *)(rd + 0x418))[*(unsigned char *)(rd + 0x414)] =
                    FS_ReadFileAsync(file, rd + (*(unsigned char *)(rd + 0x414) << 9), 0x200);
                if (((int *)(rd + 0x418))[*(unsigned char *)(rd + 0x415)] != 0 &&
                    ((int *)(rd + 0x418))[*(unsigned char *)(rd + 0x415)] == -1) {
                    OS_Terminate();
                }
            } while (func_02004484(rd + 0x400, rd + (*(unsigned char *)(rd + 0x415) << 9),
                                   ((int *)(rd + 0x418))[*(unsigned char *)(rd + 0x415)]) != 0);
        }
        FlushLoaded(buffer, len);
    } else {
        len = file[10] - file[9];
        if (len > size) {
            len = -1;
        } else {
            OS_UnlockByWord_0x0200ae4c(file, buffer, len);
        }
    }
    FS_CloseFile(file);
    return len;
}
