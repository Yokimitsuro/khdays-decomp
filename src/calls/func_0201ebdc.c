typedef unsigned int u32;

extern int *func_0201e4c8(void);
extern void FS_InitFile(void *file);
extern void FSi_WaitForCardThread(void);
extern int func_020250bc(void *file, u32 id);
extern u32 func_02025074(u32 param_1);
extern int strlen(const char *s);
extern char *func_02024e6c(char *name);
extern int FS_OpenFile(void *file, const char *path);
extern void *func_0201e5fc(
    char *self, void *file, int existing, int maxSize, int **heap, int id);
extern void *func_020236f8(u32 size, int align, int **heapPP);
extern int FS_CloseFile(char *file);
extern int OS_SendMessage(char *q, void *msg, int flags);
extern int data_0204bbfc[];
extern char data_0204bc1c[];
extern const unsigned char data_02041c48[128];

static inline int toupper(int c)
{
    return (c < 0 || c >= 128) ? c : data_02041c48[c];
}

void *func_0201ebdc(const void *data, int id)
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
        func_0201e5fc((char *)self, file, 0, 0, (int **)data_0204bbfc[5], id);
        self[1] = 1;
    } else {
        self[11] = self[4] - self[3];
        self[10] = (int)func_020236f8(self[11], 0x20, (int **)data_0204bbfc[5]);
        self[1] = 0;
    }

    data_0204bbfc[5] = 0;
    FS_CloseFile((char *)file);
    OS_SendMessage(data_0204bc1c, self, 1);
    return (void *)self[10];
}
