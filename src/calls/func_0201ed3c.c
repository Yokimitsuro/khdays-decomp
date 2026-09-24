/* func_0201ed3c -- load a file into a caller buffer through the loader thread, MAIN. Twin of
 * func_0201ebdc for a fixed destination: the file (an id with bit 31 set, or a path whose
 * language placeholder func_02024e6c expands) is opened; a ".?Z" name or a compressed id is
 * decompressed into `buffer` (func_0201e5fc, failing if it exceeds `maxSize`), anything else is
 * read raw when it fits. On success the request goes to the loader queue and the byte count is
 * returned; 0 when no request slot is free, -1 when the data does not fit. */
typedef unsigned int u32;

extern int *func_0201e4c8(void);
extern void FS_InitFile(void *file);
extern void FSi_WaitForCardThread(void);
extern int func_020250bc(void *file, u32 id);
extern u32 func_02025074(u32 param_1);
extern int strlen(const char *s);
extern char *func_02024e6c(char *name);
extern int FS_OpenFile(void *file, const char *path);
extern void *func_0201e5fc(char *self, void *file, void *existing, int maxSize, int **heap, int id);
extern int FS_CloseFile(char *file);
extern int OS_SendMessage(char *q, void *msg, int flags);
extern char data_0204bc1c[];
extern const unsigned char data_02041c48[128];

static inline int toupper(int c)
{
    return (c < 0 || c >= 128) ? c : data_02041c48[c];
}

int func_0201ed3c(const void *data, void *buffer, int maxSize)
{
    u32 file[0x12]; /* FSFile: [2] = start offset, [9] = image base, [10] = field_10 */
    int *self;
    int flag;

    self = func_0201e4c8();
    if (self == 0) {
        return 0;
    }

    FS_InitFile(file);
    FSi_WaitForCardThread();

    if ((u32)data & 0x80000000) {
        func_020250bc(file, (u32)data);
        flag = (int)func_02025074((u32)data);
    } else {
        int len = strlen((const char *)data);
        FS_OpenFile(file, func_02024e6c((char *)data));

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
        if (func_0201e5fc((char *)self, file, buffer, maxSize, 0, 0) == 0) {
            goto fail;
        }
        self[1] = 1;
    } else {
        self[11] = self[4] - self[3];
        self[10] = (int)buffer;
        self[1] = 0;
        if (self[11] > maxSize) {
            goto fail;
        }
    }

    FS_CloseFile((char *)file);
    OS_SendMessage(data_0204bc1c, self, 1);
    return self[11];

fail:
    FS_CloseFile((char *)file);
    return -1;
}
