typedef struct { unsigned int arc; unsigned int file_id; } FSFileID;

extern int func_0201b6f4(int a, void *b, int c, int d);
extern int func_0201b6a4(int a);
extern void func_0201b7c0(FSFileID *id);
extern int FS_OpenFileFast(void *file, FSFileID id);

int func_0201df84(char *r5, int r4) {
    FSFileID id;
    if (func_0201b6f4(r4, r5 + 0xa8, 0x40, 0) != 0x40) return 0;
    func_0201b7c0(&id);
    if (!FS_OpenFileFast(r5 + 0x5c, id)) return 0;
    *(int *)(r5 + 0xa4) = func_0201b6a4(r4);
    return 1;
}
