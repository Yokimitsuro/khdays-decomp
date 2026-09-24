/* func_0201e670 -- the file loader thread, MAIN. A state machine over the second reader
 * (data_0204bbfc.reader2: two 0x200-byte blocks, FSFile +0x400, current request +0x448, idle queue
 * +0x44c, block lengths +0x454, block flags +0x45c):
 *   0  idle: unless held (+0x3c) wakes the waiters and clears the request, then blocks on the
 *      request queue; a null request ends the thread. Compressed (1) / raw (0) file requests open their image
 *      (FS_OpenFileDirect) and go to 2 / 4; sound data (2) goes to 5, sound data + wave (3) to 6.
 *   2  reads block 0 (the header) and marks the first block.
 *   3  swaps the blocks, queues the next read and feeds the finished block (header word skipped
 *      once) to the uncompressor; at its end closes the file, flushes the destination and goes to 7.
 *   4  reads 0x200 bytes straight into the destination until the size is reached, then 7.
 *   5  loads the sound data (func_0201bbc8) and reports state 2 through the request.
 *   6  loads the sound data (func_0201bbf4) and its wave (func_0201bc20); reports 2 or 3.
 *   7  returns the request to the free list and goes idle.
 * A failed read terminates the thread; every busy state yields (OS_RescheduleThread). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct OSThreadQueue {
    struct OSThread *head;
    struct OSThread *tail;
} OSThreadQueue;

typedef struct LoaderRequest {
    struct LoaderRequest *next;         /* +0x00 */
    int type;                           /* +0x04 */
    union {
        struct {
            void *archive;              /* +0x08 */
            u32 imageTop;               /* +0x0c */
            u32 imageBottom;            /* +0x10 */
        } file;
        struct {
            u16 dataId;                 /* +0x08 */
            u16 waveId;                 /* +0x0a */
            void *heap;                 /* +0x0c */
            u8 *pState;                 /* +0x10 */
        } snd;
    } u;
    char uncomp[0x28 - 0x14];           /* +0x14: uncompress context */
    char *dest;                         /* +0x28 */
    int size;                           /* +0x2c */
} LoaderRequest;

typedef struct LoaderBlockFlags {
    u8 cur : 1;
    u8 prev : 1;
    u8 first : 1;
} LoaderBlockFlags;

typedef struct LoaderReader {
    char block[2][0x200];               /* +0x000 */
    char file[0x48];                    /* +0x400: FSFile */
    LoaderRequest *request;             /* +0x448 */
    OSThreadQueue idleQueue;            /* +0x44c */
    int len[2];                         /* +0x454 (raw reads: last length, bytes done) */
    LoaderBlockFlags flags;             /* +0x45c */
} LoaderReader;

typedef struct FileLoader {
    char *reader;                       /* +0x00 */
    LoaderReader *reader2;              /* +0x04 */
    char pad08[0x3c - 8];
    int hold;                           /* +0x3c */
} FileLoader;

extern FileLoader data_0204bbfc;
extern char data_0204bc1c[];            /* request queue */
extern void OS_WakeupThread(OSThreadQueue *queue);
extern int OS_ReceiveMessage(void *mq, void *msg, int flags);
extern int FS_OpenFileDirect(void *file, void *archive, u32 imageTop, u32 imageBottom, u32 fileIndex);
extern void FSi_WaitForCardThread(void);
extern int OS_UnlockByWord_0x0200ae4c(void *file, void *dst, int len);   /* FS_ReadFile */
extern int FS_ReadFileAsync(void *file, void *dst, int len);
extern void OS_Terminate(void);
extern int func_02004484(void *context, void *src, int len);
extern int FS_CloseFile(void *file);
extern void DC_FlushAll(void);
extern void DC_FlushRange(const void *startAddr, u32 nBytes);
extern int FS_WaitAsync(void *file);
extern void OS_RescheduleThread(void);
extern void func_0201bbc8(u32 dataId, void *heap);
extern int func_0201bbf4(u32 dataId, void *heap);
extern int func_0201bc20(u32 waveId, void *heap);
extern void func_0201e4f0(LoaderRequest *request);

static inline void FlushLoaded(void *buffer, u32 size)
{
    if (size >= 0x2400) {
        DC_FlushAll();
    } else {
        DC_FlushRange(buffer, size);
    }
}

void func_0201e670(void *arg)
{
    int state = 0;
    LoaderRequest *req;
    LoaderReader *rd = data_0204bbfc.reader2;

    for (;;) {
        switch (state) {
        case 0:
            if (data_0204bbfc.hold == 0) {
                OS_WakeupThread(&rd->idleQueue);
                rd->request = 0;
            }
            OS_ReceiveMessage(data_0204bc1c, &rd->request, 1);
            if (rd->request == 0) {
                return;
            }
            rd->len[1] = 0;
            rd->len[0] = 0;
            req = rd->request;
            switch (req->type) {
            case 0:
                FS_OpenFileDirect(rd->file, req->u.file.archive, req->u.file.imageTop, req->u.file.imageBottom, 0);
                state = 4;
                break;
            case 1:
                FS_OpenFileDirect(rd->file, req->u.file.archive, req->u.file.imageTop, req->u.file.imageBottom, 0);
                state = 2;
                break;
            case 2:
                state = 5;
                break;
            case 3:
                state = 6;
                break;
            }
            break;
        case 2:
            rd->flags.cur = 0;
            rd->flags.prev = 1;
            rd->flags.first = 1;
            FSi_WaitForCardThread();
            rd->len[rd->flags.cur] = OS_UnlockByWord_0x0200ae4c(rd->file, rd->block[rd->flags.cur], 0x200);
            state = 3;
            break;
        case 3:
            rd->flags.cur ^= 1;
            rd->flags.prev ^= 1;
            FSi_WaitForCardThread();
            rd->len[rd->flags.cur] = FS_ReadFileAsync(rd->file, rd->block[rd->flags.cur], 0x200);
            if (rd->len[rd->flags.prev] == 0) {
                break;
            }
            if (rd->len[rd->flags.prev] == -1) {
                OS_Terminate();
            }
            {
                char *src = rd->block[rd->flags.prev];
                int len = rd->len[rd->flags.prev];

                if (rd->flags.first) {
                    src += 4;
                    len -= 4;
                    rd->flags.first = 0;
                }
                if (func_02004484(req->uncomp, src, len) == 0) {
                    FS_CloseFile(rd->file);
                    FlushLoaded(req->dest, req->size);
                    state = 7;
                }
            }
            FS_WaitAsync(rd->file);
            OS_RescheduleThread();
            break;
        case 4:
            FSi_WaitForCardThread();
            rd->len[0] = OS_UnlockByWord_0x0200ae4c(rd->file, req->dest + rd->len[1], 0x200);
            if (rd->len[0] == -1) {
                OS_Terminate();
            } else {
                rd->len[1] += rd->len[0];
                if (rd->len[1] >= req->size) {
                    FS_CloseFile(rd->file);
                    state = 7;
                }
            }
            OS_RescheduleThread();
            break;
        case 5:
            FSi_WaitForCardThread();
            func_0201bbc8(req->u.snd.dataId, req->u.snd.heap);
            *req->u.snd.pState = 2;
            state = 7;
            OS_RescheduleThread();
            break;
        case 6:
            FSi_WaitForCardThread();
            if (func_0201bbf4(req->u.snd.dataId, req->u.snd.heap) != 0) {
                FSi_WaitForCardThread();
                *req->u.snd.pState = func_0201bc20(req->u.snd.waveId, req->u.snd.heap) ? 2 : 3;
            } else {
                *req->u.snd.pState = 3;
            }
            state = 7;
            OS_RescheduleThread();
            break;
        case 7:
            func_0201e4f0(req);
            state = 0;
            break;
        }
    }
}
