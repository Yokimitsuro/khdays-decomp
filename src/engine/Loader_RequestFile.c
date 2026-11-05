/* Queues a file load: takes a free request, opens the file (a packed-archive handle or a path in
 * the current language), sets up LZ decompression for compressed files or allocates the buffer
 * otherwise, and posts the request to the loader thread; returns the destination buffer. */

#include "nitro/types.h"
#include "game/engine.h"

extern int *Loader_PopFreeRequest(void);
extern void FS_InitFile(void *file);
extern void FSi_WaitForCardThread(void);
extern int Archive_OpenSubfileByHandle(void *file, u32 id);
extern int strlen(const char *s);
extern char *Msg_BuildLangPath(char *name);
extern int FS_OpenFile(void *file, const char *path);
extern void *Loader_SetupLZDecompress(
    char *self, void *file, int existing, int maxSize, int **heap, int id);
extern int FS_CloseFile(char *file);
extern int OS_SendMessage(char *q, void *msg, int flags);
extern int gFileLoader[];
extern char data_0204bc1c[];
extern const unsigned char data_02041c48[128];

static inline int toupper(int c)
{
    return (c < 0 || c >= 128) ? c : data_02041c48[c];
}

void *Loader_RequestFile(const void *data, int id)
{
    u32 file[0x12]; /* FSFile: [2] = start offset, [9] = image base, [10] = field_10 */
    int *self;
    int flag;

    self = Loader_PopFreeRequest();
    if (self == 0) {
        return 0;
    }

    FS_InitFile(file);
    FSi_WaitForCardThread();

    if ((u32)data & 0x80000000) {
        Archive_OpenSubfileByHandle(file, (u32)data);
        flag = (int)Archive_SubfileIsCompressed((u32)data);
    } else {
        int len = strlen((const char *)data);
        FS_OpenFile(file, Msg_BuildLangPath((char *)data));

        flag = 0;
        if (((const char *)data)[len - 2] == '.' &&
            toupper(((const char *)data)[len - 1]) == 'Z') {
            flag = 1;
        }
    }

    self[2] = file[2];
    self[3] = file[9];
    self[4] = file[10];

    if (flag != 0) {
        Loader_SetupLZDecompress((char *)self, file, 0, 0, (int **)gFileLoader[5], id);
        self[1] = 1;
    } else {
        self[11] = self[4] - self[3];
        self[10] = (int)ExpHeap_AllocOrDefault(self[11], 0x20, (GameHeap *)gFileLoader[5]);
        self[1] = 0;
    }

    gFileLoader[5] = 0;
    FS_CloseFile((char *)file);
    OS_SendMessage(data_0204bc1c, self, 1);
    return (void *)self[10];
}
