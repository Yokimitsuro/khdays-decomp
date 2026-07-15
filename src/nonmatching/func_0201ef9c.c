/* NONMATCHING (if-conversion tie, 520/524 bytes; only the extension bounds-check
 * differs): mwcc 3.0 predicates the toupper-table lookup `if(c>=0 && c<0x80) c=tbl[c]`
 * as `ldrblt` (2-instr block), whereas the ROM branches over it with `bge`. Confirmed
 * across 3.0_136_patched and 3.0_patch4; resisted nested-if, De Morgan, reversed
 * operand order, and `-1<(int)c` forms. The whole double-buffered async decompressor
 * loop and both load paths match byte-exact. Semantics complete + correct.
 *
 * Archive_LoadFile: load a card file (filename in param_1, or a packed sub-file handle
 * when bit31 is set) into a freshly allocated buffer and return it. If the data is
 * compressed (filename ending '.z' -> 'Z', or the sub-file desc[k] bit31), stream it
 * through a double-buffered async read + decompress (func_0201e508 / func_02004484);
 * otherwise allocate the raw size and read it straight. Returns 0 if the open failed. */
extern void FS_InitFile(void *f);
extern void FSi_WaitForCardThread(void);
extern int func_020250bc(void *f, unsigned int handle);
extern unsigned int func_02025074(unsigned int handle);
extern int strlen(const char *s);
extern char *func_02024e6c(char *path);
extern int FS_OpenFile(void *f, char *path);
extern void *func_0201e508(void *ctx, void *f, int a, int *outSize, void *heap,
                           unsigned int p2, int *outStatus);
extern void FS_WaitAsync(void *f);
extern int FS_ReadFileAsync(void *f, void *dst, int len);
extern void OS_Terminate(void);
extern int func_02004484(void *state, void *src, int len);
extern void DC_FlushAll(void);
extern void DC_FlushRange(void *addr, int len);
extern void *func_020236f8(int size, int align, void *heap);
extern void OS_UnlockByWord_0x0200ae4c(void *f, void *buf, int size);
extern void FS_CloseFile(void *f);
extern unsigned int data_0204bbfc[];
extern unsigned char data_02041c48[];

unsigned int func_0201ef9c(char *param_1, unsigned int param_2, int param_3, int param_4) {
    char file[0x48];
    int size;
    int status;
    int ok;
    unsigned int compressed;
    void *buf;
    char *ctx = (char *)data_0204bbfc[0];
    FS_InitFile(file);
    FSi_WaitForCardThread();
    if ((unsigned int)param_1 & 0x80000000) {
        ok = func_020250bc(file, (unsigned int)param_1);
        compressed = func_02025074((unsigned int)param_1);
    } else {
        int len = strlen(param_1);
        ok = FS_OpenFile(file, func_02024e6c(param_1));
        compressed = 0;
        if (param_1[len - 2] == '.') {
            int c = param_1[len - 1];
            if (c >= 0 && c < 0x80) {
                c = data_02041c48[c];
            }
            if (c == 0x5a) {
                compressed = 1;
            }
        }
    }
    if (ok == 0) {
        return 0;
    }
    if (compressed != 0) {
        buf = func_0201e508(ctx, file, 0, &size, (void *)data_0204bbfc[5], param_2, &status);
        if (status == 0) {
            do {
                *(unsigned char *)(ctx + 0x414) ^= 1;
                *(unsigned char *)(ctx + 0x415) ^= 1;
                FS_WaitAsync(file);
                *(int *)(ctx + (*(unsigned char *)(ctx + 0x414) << 2) + 0x418) =
                    FS_ReadFileAsync(file, ctx + (*(unsigned char *)(ctx + 0x414) << 9), 0x200);
                if (*(int *)(ctx + (*(unsigned char *)(ctx + 0x415) << 2) + 0x418) != 0 &&
                    *(int *)(ctx + (*(unsigned char *)(ctx + 0x415) << 2) + 0x418) == -1) {
                    OS_Terminate();
                }
            } while (func_02004484(ctx + 0x400, ctx + (*(unsigned char *)(ctx + 0x415) << 9),
                                   *(int *)(ctx + (*(unsigned char *)(ctx + 0x415) << 2) + 0x418)) != 0);
        }
        if (size < 0x2400) {
            DC_FlushRange(buf, size);
        } else {
            DC_FlushAll();
        }
    } else {
        size = *(int *)(file + 0x28) - *(int *)(file + 0x24);
        buf = func_020236f8(size, 0x20, (void *)data_0204bbfc[5]);
        if (buf != 0) {
            OS_UnlockByWord_0x0200ae4c(file, buf, size);
        }
    }
    data_0204bbfc[5] = 0;
    FS_CloseFile(file);
    return (unsigned int)buf;
}
